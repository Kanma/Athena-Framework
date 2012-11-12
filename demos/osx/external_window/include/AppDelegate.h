#import <Cocoa/Cocoa.h>
#import <Athena/Engine.h>
#import <Ogre/OSX/OgreOSXCocoaView.h>


@interface AppDelegate : NSObject <NSApplicationDelegate>
{
@private
    // UI
    IBOutlet NSWindow* window;
    IBOutlet OgreView* ogreView;

    // Attributes
    Athena::Engine     engine;
}

@end
