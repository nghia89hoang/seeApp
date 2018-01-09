//
//  MainViewController.m
//  see
//
//  Created by Hoang Ngoc Nghia on 1/9/18.
//

#import "MainViewController.h"
#include "cinder/app/App.h"

@interface MainViewController () {
    UIView *cinderView;
    IBOutlet UIView *previewView_;    
    IBOutlet UIView *footerView_;
}
@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)addCinderViewToFront {
    cinderView = (__bridge UIView*)ci::app::getWindow()->getNative();
    cinderView.frame = self.view.bounds;
    [previewView_ addSubview:cinderView];
}

- (void)addCinderViewAsBarButton {
    
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)dealloc {
    [previewView_ release];
    [footerView_ release];
    [super dealloc];
}
@end
