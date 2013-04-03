#import <created_window/include/AppDelegate.h>
#import <MainGameState.h>
#import <Athena/GameStates/GameStateManager.h>
#import <Athena/Tasks/TaskManager.h>

using namespace Athena;
using namespace Athena::GameStates;


@implementation AppDelegate

- (void) applicationDidFinishLaunching:(NSNotification*)aNotification
{
    // Initialize Athena
    engine.setup("athena.cfg");

    // Create the render window
    engine.createRenderWindow("MainWindow", "Example", 800, 600, false);

    // Create a gamestate and tell the Gamestate Manager about it
    GameStateManager* pGameStateManager = engine.getGameStateManager();

    pGameStateManager->registerState(1, new MainGameState());
    pGameStateManager->pushState(1);

    // Create a timer to render at 50fps
    [NSTimer scheduledTimerWithTimeInterval:0.02 target:self
                                   selector:@selector(stepOneFrame)
                                   userInfo:NULL repeats:YES];

    [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
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

@end
