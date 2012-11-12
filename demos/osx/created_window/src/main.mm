#import <Cocoa/Cocoa.h>
#import <AppDelegate.h>

int main(int argc, char *argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    AppDelegate* appDelegate = [[AppDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:appDelegate];

    int retVal = NSApplicationMain(argc, (const char**) argv);

    [pool release];

    return retVal;
}
