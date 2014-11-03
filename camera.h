#ifndef __CAMERA_H__
#define __CAMERA_H__

class wlCamera {
    public:
        void move(float x, float y, float z);
        void rotate(float x, float y);
        void set_pos(float x, float y, float z);
        void set_rot(float x, float y);

        float position[3] = {0.0f, 0.0f, 0.0f};
        float xrot = 0.0f;
        float yrot = 0.0f;
};

#endif
