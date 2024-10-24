#include <rbdl/rbdl.h>
using namespace RigidBodyDynamics::Math;

class Pose {
    private:
        Matrix3d orientation_;
        Vector3d translation_;
    public:
        Pose(Matrix3d &orientation, Vector3d &translation) : orientation_(orientation), translation_(translation) {}
        Matrix3d orientation() const {return orientation_;}
        Vector3d translation() const {return translation_;}
    protected:
        friend bool operator==(const Pose&, const Pose&);
        virtual bool isEqual(const Pose& pose) const { return oriIsEqual(pose) && translationIsEqual(pose); }
        virtual bool oriIsEqual(const Pose& pose) const { return pose.orientation() == orientation_; }
        virtual bool translationIsEqual(const Pose& pose) const { return pose.translation() == translation_; }

};

bool operator==(const Pose& lhs, const Pose& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}