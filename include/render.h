#ifndef RENDER_H
#define RENDER_H

class Render{
public:
    static Render* GetInstance(){
        static Render render;
        return &render;
    }
    void Draw();
    void Clear();
};

#endif