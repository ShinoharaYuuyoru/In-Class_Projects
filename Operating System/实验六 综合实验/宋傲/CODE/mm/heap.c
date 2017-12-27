//  <林理露>
//
//  heap.c
//  bit-miniOS
//
//  Created by 林理露 on 18/05/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include "os/kernel.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"

// 申请内存块
static void alloc_chunk(uint32_t start, uint32_t len);

// 释放内存块
static void free_chunk(header_t *chunk);

// 切分内存块
static void split_chunk(header_t *chunk, uint32_t len);

// 合并内存块
static void glue_chunk(header_t *chunk);

static uint32_t heap_max = HEAP_START;

// 内存块管理头指针
static header_t *heap_first;

void init_heap()
{
    heap_first = 0;
}

void *kmalloc(uint32_t len)
{
    // 把申请的内存长度加上头结构的长度，以便存储内存管理头结构
    len += sizeof(header_t);
    
    header_t *cur_header = heap_first;
    header_t *prev_header = 0;
    
    while (cur_header) {
        // 如果当前内存块未被申请过且长度大于待申请的块
        if (cur_header->allocated == 0 && cur_header->length >= len) {
            // 按当前长度切割内存
            split_chunk(cur_header, len);
            cur_header->allocated = 1;
            // 返回的时候必须将指针挪到管理头结构之后
            return (void *)((uint32_t)cur_header + sizeof(header_t));
        }
        // 逐次移动指针
        prev_header = cur_header;
        cur_header = cur_header->next;
    }
    
    uint32_t chunk_start;
    
    // 第一次执行此函数则初始化内存块初始位置
    // 后面每次根据当前指针加上申请块的长度
    if (prev_header) {
        chunk_start = (uint32_t)prev_header + prev_header->length;
    } else {
        chunk_start = HEAP_START;
        heap_first = (header_t *)chunk_start;
    }
    
    // 检测是否需要申请内存页
    alloc_chunk(chunk_start, len);
    cur_header = (header_t *)chunk_start;
    cur_header->prev = prev_header;
    cur_header->next = 0;
    cur_header->allocated = 1;
    cur_header->length = len;
    
    if (prev_header) {
        prev_header->next = cur_header;
    }
    
    return (void*)(chunk_start + sizeof(header_t));
}

void kfree(void *p)
{
    // 指针回退到管理头结构，并将已使用标记置为 0
    header_t *header = (header_t*)((uint32_t)p - sizeof(header_t));
    header->allocated = 0;
    
    // 合并内存块
    glue_chunk(header);
}

void alloc_chunk(uint32_t start, uint32_t len)
{
    // 如果当前堆的位置已达到界限则申请新的内存页
    // 必须要循环申请内存页，直到有到足够的可用内存为止
    while (start + len > heap_max) {
        uint32_t page = pmm_alloc_page();
        map(pgd_kern, heap_max, page, PAGE_PRESENT | PAGE_WRITE);
        heap_max += PAGE_SIZE;
    }
}

void free_chunk(header_t *chunk)
{
    if (chunk->prev == 0) {
        heap_first = 0;
    } else {
        chunk->prev->next = 0;
    }
    
    // 空闲的内存超过 1 页则释放掉
    while ((heap_max - PAGE_SIZE) >= (uint32_t)chunk) {
        heap_max -= PAGE_SIZE;
        uint32_t page;
        get_mapping(pgd_kern, heap_max, &page);
        unmap(pgd_kern, heap_max);
        pmm_free_page(page);
    }
}

void split_chunk(header_t *chunk, uint32_t len)
{
    // 切分内存块时需保证切分之后的剩余内存至少能容纳一个内存管理头结构
    if (chunk->length - len > sizeof (header_t)) {
        header_t *newchunk = (header_t *)((uint32_t)chunk + len);
        newchunk->prev = chunk;
        newchunk->next = chunk->next;
        newchunk->allocated = 0;
        newchunk->length = chunk->length - len;
        
        chunk->next = newchunk;
        chunk->length = len;
    }
}

void glue_chunk(header_t *chunk)
{
    // 如果该内存块后面链接有内存块且未被使用则合并
    if (chunk->next && chunk->next->allocated == 0) {
        chunk->length = chunk->length + chunk->next->length;
        if (chunk->next->next) {
            chunk->next->next->prev = chunk;
        }
        chunk->next = chunk->next->next;
    }
    
    // 如果该内存块前面链接有内存块且未被使用则合并
    if (chunk->prev && chunk->prev->allocated == 0) {
        chunk->prev->length = chunk->prev->length + chunk->length;
        chunk->prev->next = chunk->next;
        if (chunk->next) {
            chunk->next->prev = chunk->prev;
        }
        chunk = chunk->prev;
    }
    
    // 假如该内存后面没有内存块则直接释放掉
    if (chunk->next == 0) {
        free_chunk(chunk);
    }
}

void test_heap()
{
    printk_color(dc_black, dc_magenta, "kmalloc() and kfree() tests:\n\n");
    
    void *address1 = kmalloc(60);
    printk("kmalloc 60 byte at 0x%X\n", address1);
    void *address2 = kmalloc(600);
    printk("kmalloc 600 byte at 0x%X\n", address2);
    void *address3 = kmalloc(6000);
    printk("kmalloc 6000 byte at 0x%X\n", address3);
    void *address4 = kmalloc(60000);
    printk("kmalloc 60000 byte at 0x%X\n\n", address4);
    
    printk("kfree mem at 0x%X\n", address1);
    kfree(address1);
    printk("kfree mem at 0x%X\n", address2);
    kfree(address2);
    printk("kfree mem at 0x%X\n", address3);
    kfree(address3);
    printk("kfree mem at 0x%X\n\n", address4);
    kfree(address4);
}

//  </林理露>
