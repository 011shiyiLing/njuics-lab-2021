#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

//定义结构体表示cache行
typedef struct
{
  int valid;//有效位
  int tag;//标记
  uint32_t data[BLOCK_SIZE];//数据
  int dirty_bit;//脏位
}cache_line;

static cache_line *cache;
static int group_width,every_group_line;
static uint64_t line_num,group_num;

//随机替换
int random_replacement(int group_no)
{
  int random_num = rand();
  int replace_no = group_no*every_group_line + (random_num  % every_group_line);

  //write back(只有当cache行中的主存快被替换时，才将该主存快内容一次性写回主存)
  if(cache[replace_no].dirty_bit == 1)
  {
    uintptr_t block_num = (cache[replace_no].tag << group_width) + group_no;
    mem_write(block_num,(uint8_t *)cache[replace_no].data);
    //clear
    for(int j=0; j<BLOCK_SIZE; j++)
    {
      cache[replace_no].data[j] = 0;
    }
    cache[replace_no].valid = 0;
    cache[replace_no].dirty_bit = 0;
    cache[replace_no].tag = 0; 
  }
  return replace_no;
}

// TODO: implement the following functions

// 从 cache 中读出 addr 地址处的 4 字节数据
// 若缺失，需要先从内存中读入数据
uint32_t cache_read(uintptr_t addr) {
  int tag = addr >> (group_width + 6);//tag
  int group_no = (addr >> 6) & (mask_with_len(group_width)); //主存对应的cache组号
  int group_addr = (addr&0x3f) >> 2;//组内地址

  for(int i= group_no*every_group_line; i < (group_no+1)*every_group_line; i++)
  {
    if(((cache[i].tag == tag) & (cache[i].valid)))
    {
      return cache[i].data[group_addr];
    }
  }

  //缺失,从内存中读入数据
  uintptr_t block_num = addr >> 6;//主存块号
  for(int i= group_no*every_group_line; i < (group_no+1)*every_group_line; i++)
  {
    if(cache[i].valid == 0)
    {
      mem_read(block_num,(uint8_t *)cache[i].data);
      cache[i].valid = 1;
      cache[i].tag = tag;
      cache[i].dirty_bit = 1;
      return cache[i].data[group_addr];
    }
  }

  //满了，采取随机替换
  int replacement_no = random_replacement(group_no);
  mem_read(block_num,(uint8_t *)cache[replacement_no].data);
  cache[replacement_no].valid = 1;
  cache[replacement_no].tag = tag;
  cache[replacement_no].dirty_bit = 1;
  return cache[replacement_no].data[group_addr];
}

// 往 cache 中 addr 地址所属的块写入数据 data，写掩码为 wmask/ ((1 << 6) * (1 << associativity_width))
// 例如当 wmask 为 0xff 时，只写入低8比特
// 若缺失，需要从先内存中读入数据
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  int tag = addr >> (group_width + 6);//tag
  int group_no = (addr >> 6) & (mask_with_len(group_width)); //主存对应的cache组号
  int group_addr = (addr&0x3f) >> 2;//组内地址

  for(int i= group_no*every_group_line; i < (group_no+1)*every_group_line; i++)
  {
    if(((cache[i].tag == tag) & (cache[i].valid)))
    {
      cache[i].data[group_addr] = (cache[i].data[group_addr] & (~wmask)) | (data & wmask);
      cache[i].dirty_bit = 1;
      return;
    }
  }

  //缺失,从内存中读入数据
  uintptr_t block_num = addr >> 6;//主存块号
  int new_line;
  for(int i= group_no*every_group_line; i < (group_no+1)*every_group_line; i++)
  {
    if(cache[i].valid == 0)
    {
      mem_read(block_num,(uint8_t *)cache[i].data);
      //write
      cache[i].data[group_addr] = (cache[i].data[group_addr] & (~wmask)) | (data & wmask);
      cache[i].tag = tag;
      cache[i].valid = 1;
      cache[i].dirty_bit = 1;
      return;
    }
  }

  //满了，采取随机替换
  int replacement_no = random_replacement(group_no);
  mem_read(block_num,(uint8_t *)cache[replacement_no].data);
  //write
  cache[replacement_no].data[group_addr] = (cache[replacement_no].data[group_addr] & (~wmask)) | (data & wmask);
  cache[replacement_no].tag = tag;
  cache[replacement_no].valid = 1;
  cache[replacement_no].dirty_bit = 1;
  return;

}

// 初始化一个数据大小为 2^total_size_width B，关联度为 2^associativity_width 的 cache
// 例如 init_cache(14, 2) 将初始化一个 16KB，4 路组相联的cache
// 将所有 valid bit 置为无效即可
void init_cache(int total_size_width, int associativity_width) {
  group_width = total_size_width - 6 - associativity_width;
  group_num = 1 << (group_width); //cache总组数
  line_num = 1 << (total_size_width - 6); //cache总行数
  every_group_line = 1 << (associativity_width); //cache每组的行数 “几路总相联”
  //init
  cache = (cache_line *)malloc(sizeof(cache_line)*line_num);
  for(int i=0; i<line_num; i++)
  {
    cache[i].valid = 0;
    cache[i].dirty_bit = 0;
    cache[i].tag = 0;
    
    for(int j=0; j<BLOCK_SIZE; j++)
    {
      cache[i].data[j] = 0;
    }
  }
}

void display_statistic(void) {
}
