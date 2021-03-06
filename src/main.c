#include <ecs_graphics.h>

#define MOVE_SPEED (5)

void MoveSquare(ecs_rows_t *rows) {
    ECS_COLUMN(rows, EcsInput, input, 1);
    ECS_COLUMN(rows, EcsPosition2D, position, 2);

    int x_v = input->keys[ECS_KEY_D].state || input->keys[ECS_KEY_RIGHT].state;
        x_v -= input->keys[ECS_KEY_A].state || input->keys[ECS_KEY_LEFT].state;
    int y_v = input->keys[ECS_KEY_S].state || input->keys[ECS_KEY_DOWN].state;
        y_v -= input->keys[ECS_KEY_W].state || input->keys[ECS_KEY_UP].state;

    position->x += x_v * MOVE_SPEED;
    position->y += y_v * MOVE_SPEED;
}

void SomeTest(ecs_rows_t *rows) {

}

int main(int argc, char *argv[]) {
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsComponentsTransform, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGeometry, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGraphics, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsInput, ECS_2D);
    ECS_IMPORT(world, FlecsSystemsSdl2, ECS_2D);

    /* Define entity for square */
    ECS_ENTITY(world, Square, EcsPosition2D, EcsSquare, EcsColor);

    /* Define system that moves the square on keyboard input */
    ECS_SYSTEM(world, MoveSquare, EcsOnUpdate, EcsInput, Square.EcsPosition2D);

    ECS_SYSTEM(world, SomeTest, EcsOnUpdate, EcsPosition2D, !$.EcsPosition2D);

    /* Initialize canvas */
    ecs_set(world, 0, EcsCanvas2D, {
        .window = { .width = 800, .height = 600 }, .title = "Hello ecs_graphics!" 
    });

    /* Initialize square */
    ecs_set(world, Square, EcsPosition2D, {0, 0});
    ecs_set(world, Square, EcsSquare, { .size = 50 });
    ecs_set(world, Square, EcsColor, { .r = 0, .g = 0, .b = 255, .a = 255 });

    /* Enter main loop */
    ecs_set_target_fps(world, 60);

    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
