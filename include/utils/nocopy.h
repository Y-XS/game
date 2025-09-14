#ifndef NOCOPY_H
#define NOCOPY_H

class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
    
    // 删除拷贝操作
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    // 允许移动操作（可选）
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

#endif