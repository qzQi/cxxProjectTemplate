#pragma once

#ifdef USE_TCMALLOC
#include <google/tcmalloc.h>
#endif

#include <cstdlib>
#include <new>

namespace common {

// 内存池管理类
class MemoryPool {
public:
    // 分配内存
    static void* allocate(size_t size) {
#ifdef USE_TCMALLOC
        void* ptr = tc_malloc(size);
#else
        void* ptr = std::malloc(size);
#endif
        if (!ptr && size != 0) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    // 释放内存
    static void deallocate(void* ptr) {
#ifdef USE_TCMALLOC
        tc_free(ptr);
#else
        std::free(ptr);
#endif
    }

    // 重新分配内存
    static void* reallocate(void* ptr, size_t new_size) {
#ifdef USE_TCMALLOC
        return tc_realloc(ptr, new_size);
#else
        return std::realloc(ptr, new_size);
#endif
    }

    // 获取已分配内存大小（如果支持）
    static size_t getAllocatedSize(void* ptr) {
#ifdef USE_TCMALLOC
        return tc_malloc_size(ptr);
#else
        // 在标准库中无法获取实际分配大小，返回0
        return 0;
#endif
    }

    // 释放未使用的内存
    static void releaseFreeMemory() {
#ifdef USE_TCMALLOC
        tc_release_free_memory();
#endif
    }
};

// 重载全局new/delete操作符（可选）
#ifdef USE_MEMORY_POOL_GLOBAL
void* operator new(size_t size) {
    return MemoryPool::allocate(size);
}

void operator delete(void* ptr) noexcept {
    MemoryPool::deallocate(ptr);
}

void* operator new[](size_t size) {
    return MemoryPool::allocate(size);
}

void operator delete[](void* ptr) noexcept {
    MemoryPool::deallocate(ptr);
}
#endif

} // namespace common