//
//  ParticleController.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/20/18.
//

#include "ParticleController.h"
#include "Particle.h"
#include <cinder/Rand.h>
#include <list>

using namespace ci;
using namespace cinder;
using namespace cinder::app;

namespace see {
 
    ParticleController::ParticleController() {
        perlin = Perlin();
    }
    void ParticleController::update(vec2 mousePos) {

        for(std::list<ParticleRef>::iterator itr = mParticles.begin();
            itr != mParticles.end(); ) {
            if( (*itr)->mIsDead ) {
                itr = mParticles.erase(itr);
            } else {
                (*itr)->update(perlin, mousePos, mBackgroundChannel);
                ++itr;
            }
        }
    }
   
    void ParticleController::draw() {
        for(std::list<ParticleRef>::iterator itr = mParticles.begin();
            itr != mParticles.end(); ++itr) {
            (*itr)->draw();
        }
    }
    
    void ParticleController::removeParticles(int amt) {
        for(int i = 0; i < amt; ++i) {
            mParticles.pop_back();
        }
    }
    
    void ParticleController::addParticles(int amt) {
        for(int i = 0; i < amt; ++i) {
            float x = Rand::randFloat(getWindowWidth());
            float y = Rand::randFloat(getWindowHeight());
            float size = Rand::randFloat(mSizeRange.x, mSizeRange.y);
            ParticleRef p(new Particle(vec3(x,y,0), size));
            mParticles.push_back(p);
        }
    }
    
    void ParticleController::addParticles(int amt, vec2 loc, vec2 initVel, float size) {
        for(int i = 0; i < amt; ++i) {
            if(size == 0.f) {
                size = Rand::randFloat(mSizeRange.x, mSizeRange.y);
            }
            vec2 posOff = Rand::randVec2() * Rand::randFloat(15.f);
            vec2 newPos = loc + posOff;
            ParticleRef p(new Particle(vec3(newPos.x,newPos.y,0), size));
            vec2 dir = normalize(initVel + posOff);
            p->mDirection = vec3(dir.x, dir.y, 0);
            p->mVelocity = length(initVel) * Rand::randFloat(0.01f,0.22f);
            mParticles.push_back(p);
        }
    }
    
    ParticleRef ParticleController::addParticlePatternNorm(int xi, int yi, float size) {
        float x = (xi+0.5)*size;
        float y = (yi+0.5)*size;
        float csize = Rand::randFloat(mSizeRange.x, mSizeRange.y);
        ParticleRef p(new Particle(vec3(x,y,0),csize));
        mParticles.push_back(p);
        return p;
    }
    ParticleRef ParticleController::addParticlePatternCircle(int xi, int yi, float size) {
        float x = (xi+0.5)*size;
        float y = (yi+0.5)*size;
        float csize = cos(x*0.1) + sin(y*0.1) + 2.0f;
        ParticleRef p(new Particle(vec3(x,y,0),csize));
        mParticles.push_back(p);
        return p;
    }
    ParticleRef ParticleController::addParticlePatternWierd1(int xi, int yi, float size) {
        float x = (xi+0.5)*size;
        float y = (yi+0.5)*size;
        float xyOffset = sin( cos( sin(y*0.31) + cos(x*0.31) ) ) + 1;
        float csize = xyOffset * xyOffset * 1.5f;
        ParticleRef p(new Particle(vec3(x,y,0),csize));
        mParticles.push_back(p);
        return p;
    }
    ParticleRef ParticleController::addParticlePatternSpiral(int xi, int yi, float size) {
        float x = (xi+0.5)*size;
        float y = (yi+0.5)*size;
        float csize = ( sin( y * x ) + 0.5f ) * 2.5f;
        ParticleRef p(new Particle(vec3(x,y,0),csize));
        mParticles.push_back(p);
        return p;
    }
}
