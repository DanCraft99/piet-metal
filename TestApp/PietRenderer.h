//  Copyright 2019 The xi-editor authors.

#include <MetalKit/MetalKit.h>

@interface PietRenderer : NSObject<MTKViewDelegate>

- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView;

@end
