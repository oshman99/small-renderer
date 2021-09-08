#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include <hittable.h>
#include <vector>
#include <memory>
class HittableList : public Hittable 
{
    public:
        HittableList();
    public:
    //wtf is this?? shared_ptr???
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif