#import <external_window/include/AppDelegate.h>
#import <MainGameState.h>
#import <Athena/GameStates/GameStateManager.h>
#import <Athena/Tasks/TaskManager.h>

using namespace Athena;
using namespace Athena::GameStates;


@implementation AppDelegate

- (void) applicationDidFinishLaunching:(NSNotification*)aNotification
{
    // Initialize Athena
    engine.setup(std::string("demos.cfg"));

    // Create the Ogre view
    NSRect frame = [ogreView frame];
    engine.createRenderWindow((size_t) ogreView, "OgreView", (int) frame.size.width,
                              (int) frame.size.height, false);

    // Create a gamestate and tell the Gamestate Manager about it
    GameStateManager* pGameStateManager = engine.getGameStateManager();

    pGameStateManager->registerState(1, new MainGameState());
    pGameStateManager->pushState(1);

    // Create a timer to render at 50fps
    [NSTimer scheduledTimerWithTimeInterval:0.02 target:self
                                   selector:@selector(stepOneFrame)
                                   userInfo:NULL repeats:YES];

    [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];

    NSNotificationCenter* c = [NSNotificationCenter defaultCenter];
    [c addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:window];
}


- (void) stepOneFrame
{
    try
    {
        engine.getTaskManager()->step();
    }
    catch (Ogre::Exception& e)
    {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
}


- (void) windowWillClose:(NSNotification*)aNotification
{
    NSNotificationCenter* c = [NSNotificationCenter defaultCenter];
    [c removeObserver:self name:NSWindowWillCloseNotification object:nil];

    engine.destroy();
    [NSApp terminate:self];
}

@end
