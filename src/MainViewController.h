//
//  MainViewController.h
//  see
//
//  Created by Hoang Ngoc Nghia on 1/9/18.
//
#if defined(CINDER_COCOA_TOUCH)
#import <UIKit/UIKit.h>

#include "cinder/Function.h"

@interface MainViewController : UIViewController

- (void)addCinderViewToFront;
- (void)addCinderViewAsBarButton;

@property (nonatomic) std::function<void()>nextButtonCallback;
@property (nonatomic) std::function<void()>prevButtonCallback;
@end
#endif
