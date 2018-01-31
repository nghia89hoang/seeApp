//
//  Particle.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/9/18.
//

#include "Particle.h"
#include <cinder/Rand.h>

using namespace cinder;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace see {
    Particle::Particle(const vec3 &position, float radius, float mass, float drag) {
        mPosition = position;
        mRadius = radius;
        mMass = mass;
        mDrag = drag;
        mPrevPosition = position;
        mForces = vec3(0.0f);
        mDirection = Rand::randVec3();
        mVelocity = Rand::randFloat(5.0f);
        mSize = vec2(radius);
        pause = false;
        mScale = 1.0;
        mDirToTarget = vec2(1,1);
        mUpdateMode = 0;
        mLifeSpan = Rand::randInt(50, 200);
        mDecay = Rand::randFloat(0.95f, 0.99f);
        mAge = 0;
        mIsDead = false;
    }
    void Particle::update(Perlin perlin, vec2 target, Channel32fRef c) {
        if(!pause) {
            if(mAge > mLifeSpan) {
                mIsDead = true;
                return;
            } else {
                mAge++;
            }
            float value = c->getValue(vec2(mPosition.x, mPosition.y));
            mDirToTarget = target - vec2(mPosition.x, mPosition.y);
            switch(mUpdateMode) {
                case 1:{
                    mDirToTarget = normalize(mDirToTarget);
                    mDirection = vec3(mDirToTarget.x, mDirToTarget.y, 0);
                    mPosition = mPosition + mDirection * 100.0f;
                    mPosition.x = constrain(mPosition.x, 0.0f, (c->getWidth() - 1.0f));
                    mPosition.y = constrain(mPosition.y, 0.0f, (c->getHeight() - 1.0f));
                }
                    break;
                case 2: {
                    float time = getElapsedSeconds() * 1.0f;
                    float dist = mDirToTarget.length() * 0.05;
                    float sinOffset = sin(dist - time);
                    mDirToTarget = normalize(mDirToTarget);
                    mDirection = vec3(mDirToTarget.x, mDirToTarget.y, 0);
                    mPosition = mPosition + mDirection * sinOffset;
                    mPosition.x = constrain( mPosition.x, 0.0f, c->getWidth() - 1.0f );
                    mPosition.y = constrain( mPosition.y, 0.0f, c->getHeight() - 1.0f );
                }
                    break;
                case 3: {
                    float time = getElapsedSeconds() * 1.0f;
                    float dist = mDirToTarget.length() * 0.05;
                    float sinOffset = sin(dist - time);
                    mSize.x = value * mScale;
                    mDirToTarget *= sinOffset * 15.0f;
                    mDirection = vec3(mDirToTarget.x, mDirToTarget.y, 0);
                    mPosition = mPosition + mDirection;
                }
                    break;
                default:
                    float nZ = app::getElapsedSeconds() * 0.1f;
                    float noise = perlin.fBm(mPosition.x * 0.005f, mPosition.y * 0.005f, nZ);
                    float angle = noise * 15.0f;
                    mColor = ColorA(sin(mVelocity), cos(noise * mVelocity), sin(noise), 1.0f - (float)mAge/mLifeSpan);
                    mDirection += vec3(cos(angle), sin(angle), 0.0f);
                    mPosition = mPosition + mDirection * mVelocity;
                    mVelocity *= mDecay;
                    
                    break;
            }
        }
    }
    void Particle::draw() {
        gl::ScopedColor c(mColor);
        
        float size = mSize.x * (1.0f - mAge/mLifeSpan);
        Rectf rect( mPosition.x, mPosition.y, mPosition.x + size, mPosition.y + size );
        gl::drawSolidRect(rect);
        
#if DEBUG_ARR
        float arrowLength = 15.0f;
        vec3 p1(mPosition);
        vec3 p2(mPosition + vec3(mDirToTarget, 0) * arrowLength);
        float headLength = 6.0f;
        float headRadius = 3.0f;
        gl::drawVector(p1, p2, headLength, headRadius);
#endif
    }
}
