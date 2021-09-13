#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include <hittable.h>
#include <vector>
#include <memory>
//NOTE:: this is used in vector as type, so vector can adapt to size of Hittable-derived onjects we add to it
//using just Hittable is not an option - derived objects will be cut to memory size of just Hittble object. shared_ptr eases memory management,
//but other types of ptr can be considered
typedef std::shared_ptr<Hittable> HittableObjectPtr;
class HittableList : public Hittable 
{
    public:
        HittableList() {};
        HittableList(HittableObjectPtr object) { add(object); }
        void add(HittableObjectPtr object) { objects.push_back(object); }
        void clear() { objects.clear(); }
        
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    public:
    std::vector<HittableObjectPtr> objects;
};

bool HittableList::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool is_anything_hit = false;
    auto closest_so_far = t_max;
    
    for(const auto& object: objects)
    {
        if(object->hit(r, t_min, closest_so_far, temp_rec))
        { 
            is_anything_hit = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return is_anything_hit;
}

#endif