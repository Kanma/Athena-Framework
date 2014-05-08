#import <Cocoa/Cocoa.h>
#import <Athena/Engine.h>
#import <Ogre/OSX/OgreOSXCocoaView.h>


@interface AppDelegate : NSObject <NSApplicationDelegate>
{
@private
    // Attributes
    Athena::Engine engine;
}

@end
