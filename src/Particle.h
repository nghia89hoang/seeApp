//
//  Particle.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/9/18.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include <cinder/Perlin.h>
using namespace cinder;
using namespace ci;
using namespace std;

namespace see {
    
class Particle;
typedef std::shared_ptr<Particle> ParticleRef;
    
class Particle {
public:
    Particle(const vec3 &position, float radius=5.0f, float mass=0.0f, float drag=0.0f);
    virtual ~Particle(){}
    
    bool pause;
    int mUpdateMode;
    int mAge;
    int mLifeSpan;
    float mDecay;
    bool mIsDead;
    
    vec3 mPosition, mPrevPosition;
    vec3 mForces;
    vec3 mDirection;
    vec2 mSize;
    vec2 mDirToTarget;
    ColorA mColor;
    
    float mScale;
    float mVelocity;
    float mRadius;
    float mMass;
    float mDrag;
    
    void update(Perlin perlin, vec2 target = vec2(-1,-1),Channel32fRef c=nullptr);
    void draw();
};
    
}

#endif /* Particle_hpp */
