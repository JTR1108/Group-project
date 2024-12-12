#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIALOGUE_LENGTH 500
#define MAX_NAME_LENGTH 16
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_INVENTORY_SIZE 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int maxHealth;
    int attack;
    int gold;
    char inventory[MAX_INVENTORY_SIZE][MAX_NAME_LENGTH];
    int itemCount;
} Player;

typedef struct Room {
    char name[50];
    char description[200];
    char item[50];
    int hasItem;
    int locked;
} Room;

typedef struct Enemy {
    char name[50];
    int health;
    int isAlive;
} Enemy;

struct Quest {
    int isActive;
    int isCompleted;
    char targetItem[50];
    int rewardGold;
    char description[200];
};

struct NPC {
    char name[50];
    char dialogue[200]; 
    int hasQuest;
    struct Quest quest;
};



void intro(Player *player);
void Tavern(Player *player);
void mountainsEncounter(Player *player);
void explorePath(Player *player);
void riverCrossing(Player *player);
void caveEncounter(Player *player);
void farmersField(Player *player);
void combat(Player *player, Enemy *enemy);
void printInventory(Player *player);
void pickUpItem(Player *player, Room *room);
void unlockRoom(Player *player, Room *room);
void shop(Player *player);
void interactWithNPC(Player *player, struct NPC *npc);
void townSquare(Player *player);
void oldLadyBridge(Player *player);
void bridgeEncounter(Player *player);

int main() {
    Player player;
    intro(&player);
    
    int choice;

    printf("--------------------------------------------------------------------------\n\n");
    
    Tavern(&player);
    
    return 0;
}

void intro(Player *player) {
    printf("\n=================================\n");
    printf("Welcome to the Text Adventure Game\n");
    printf("=================================\n\n");

    char tempName[MAX_NAME_LENGTH + 1];  // +1 for null terminator
    printf("Hello traveler, what is your name? (max 15 characters): ");
    scanf("%15s", tempName);  // Limits input to 15 characters
    while (getchar() != '\n');  // Clear input buffer

    // Copy name to player structure
    strncpy(player->name, tempName, MAX_NAME_LENGTH);
    player->name[MAX_NAME_LENGTH] = '\0';  // Ensure null termination
    
    printf("\nWell, %s, good luck.\n\nYou find yourself in a cozy tavern, seemingly waking from a dream\n\n", player->name);
    
    // Initialize player stats
    player->health = 100;
    player->maxHealth = 100;
    player->attack = 10;
    player->gold = 50;
    player->itemCount = 0;
    
    printf("Your starting stats:\n");
    printf("Health: %d/%d\n", player->health, player->maxHealth);
    printf("Attack: %d\n", player->attack);
    printf("Gold: %d\n", player->gold);
    printf("\nPress Enter to continue...");
    getchar();
}

void Tavern(Player *player) {
     int choice;
    
    do{
    printf("\nYou see some other people in the tavern. What would you like to do?\n\n");
    printf("1. Talk to people\n");
    printf("2. Go outside\n\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nThe people around you are too drunk to talk coherently. You're not getting anywhere.\n\n");
        printf("\nYou decide to start your adventure.\n\n");
        townSquare(player);
    } else if (choice == 2) {
        printf("\nYou decide to start your adventure.\n\n");
        townSquare(player);
        return;
    }
    } while (choice != 2);
}

void townSquare(Player *player) {
    int choice;

    printf("You step into the bustling town of Dunberry. A glistening fountain greets you in the town square, and nearby, you notice a small shop with a large map displayed prominently.\n\n");

    do {
        printf("What would you like to do?\n\n");
        printf("1. Open Inventory\n");
        printf("2. Go to Shop\n");
        printf("3. Inspect Map\n");
        printf("4. Continue on the path\n\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printInventory(player);
                break;
            case 2:
                shop(player);
                break;
            case 3:
                printf("\nYou study the map displayed on the shop wall. It outlines the surrounding regions:\n\n");
                printf("- To the north: a mysterious cave said to hold secrets.\n\n");
                printf("- To the south: a cute farm that needs help.\n\n");
                printf("- To the east: a fast-flowing river splitting the land in two.\n\n");
                printf("- To the northeast: a graveyard where the undead lives.\n\n");
                printf("- To the southeast: towering mountains rumored to be home to ancient creatures.\n\n");
                printf("- Far to the east: the Crystal Kingdom, where the evil lich rules with an iron fist.\n\n");
                printf("The map ends there, not showing anything else.\n\n");
                break;
            case 4:
                printf("\nYou decide to leave and continue on the path.\n\n");
                explorePath(player);
                return;
            default:
                printf("\nInvalid choice. Please choose again.\n\n");
        }
    } while (choice != 4);
}

void shop(Player *player) {
    int itemChoice;

    printf("\nHere are my wares:\n\n");
    printf("1. Health Potion: 10 gold (Restores 20 health)\n\n");
    printf("2. Apple: 2 gold (Restores 5 health)\n\n");
    printf("3. Short Sword: 20 gold (+10 damage in combat)\n\n");
    printf("4. Secret Key: 50 gold (Unlocks a mysterious chest somewhere far away)\n\n");
    printf("5. Damage Potion: 15 gold (Deals 50 damage to an enemy)\n\n");
    printf("6. Exit Shop\n\n");
    printf("Gold: %d\n\n", player->gold);

    while (1) {
        printf("What would you like to buy? ");
        scanf("%d", &itemChoice);

        switch (itemChoice) {
            case 1:
                if (player->gold >= 10) {
                    player->gold -= 10;
                    strcpy(player->inventory[player->itemCount], "Health Potion");
                    player->itemCount++;
                    printf("\nYou bought a Health Potion! Remaining gold: %d\n\n", player->gold);
                } else {
                    printf("\nYou don't have enough gold for a Health Potion.\n\n");
                }
                break;
            case 2:
                if (player->gold >= 2) {
                    player->gold -= 2;
                    strcpy(player->inventory[player->itemCount], "Apple");
                    player->itemCount++;
                    printf("\nYou bought an Apple! Remaining gold: %d\n\n", player->gold);
                } else {
                    printf("\nYou don't have enough gold for an Apple.\n\n");
                }
                break;
            case 3:
                if (player->gold >= 20) {
                    player->gold -= 20;
                    strcpy(player->inventory[player->itemCount], "Short Sword");
                    player->itemCount++;
                    printf("\nYou bought a Short Sword! You feel stronger. Remaining gold: %d\n\n", player->gold);
                } else {
                    printf("\nYou don't have enough gold for the Short Sword.\n\n");
                }
                break;
            case 4:
                if (player->gold >= 50) {
                    player->gold -= 50;
                    strcpy(player->inventory[player->itemCount], "Secret Key");
                    player->itemCount++;
                    printf("\nYou bought the Secret Key! You wonder what it unlocks. Remaining gold: %d\n\n", player->gold);
                } else {
                    printf("\nYou don't have enough gold for the Secret Key.\n\n");
                }
                break;
            case 5:
                if (player->gold >= 15) {
                    player->gold -= 15;
                    strcpy(player->inventory[player->itemCount], "Damage Potion");
                    player->itemCount++;
                    printf("\nYou bought a Damage Potion! Enemies beware. Remaining gold: %d\n\n", player->gold);
                } else {
                    printf("\nYou don't have enough gold for the Damage Potion.\n\n");
                }
                break;
            case 6:
                printf("\nThanks for visiting the shop!\n\n");
                return;
            default:
                printf("\nInvalid choice. Please choose a valid item.\n\n");
        }
    }
}

void graveyardEncounter(Player *player) {
    Enemy skeletons[3] = {
        {"Skeleton Warrior 1", 30, 1},
        {"Skeleton Warrior 2", 30, 1},
        {"Skeleton Warrior 3", 30, 1}
    };
    int choice;

    printf("\nYou cross the old lady's bridge and arrive at the graveyard.\n\n");
    printf("The air grows cold, and the ground is littered with crumbling tombstones.\n\n");
    printf("A dark aura fills the area, and as you step further in, three skeleton warriors rise from the ground, their bones rattling ominously.\n\n");
    printf("They attack you as a group!\n\n");

    while ((skeletons[0].isAlive || skeletons[1].isAlive || skeletons[2].isAlive) && player->health > 0) {
        printf("\nYour health: %d\n", player->health);
        printf("Skeletons remaining:\n");
        for (int i = 0; i < 3; i++) {
            if (skeletons[i].isAlive) {
                printf("- %s: %d health\n", skeletons[i].name, skeletons[i].health);
            }
        }

        printf("\nWhat will you do?\n");
        printf("1. Attack a skeleton\n");
        printf("2. Open inventory\n");
        printf("3. Attempt to flee\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Choose which skeleton to attack
                printf("\nChoose your target:\n");
                for (int i = 0; i < 3; i++) {
                    if (skeletons[i].isAlive) {
                        printf("%d. %s\n", i + 1, skeletons[i].name);
                    }
                }
                int target;
                scanf("%d", &target);
                target -= 1;  // Convert to zero-based index

                if (target >= 0 && target < 3 && skeletons[target].isAlive) {
                    printf("\nYou attack %s!\n", skeletons[target].name);
                    skeletons[target].health -= 20;
                    if (skeletons[target].health <= 0) {
                        printf("You have slain %s!\n", skeletons[target].name);
                        skeletons[target].isAlive = 0;
                    } else {
                        printf("%s has %d health remaining.\n", skeletons[target].name, skeletons[target].health);
                    }
                } else {
                    printf("\nInvalid target or the skeleton is already defeated.\n");
                }
                break;
            }

            case 2:
                printInventory(player);
                break;

            case 3: {
                printf("\nYou attempt to flee from the graveyard!\n");
                int escapeNumber, correctEscapeNumber = rand() % 3 + 1;
                printf("Pick a number (1-3): ");
                scanf("%d", &escapeNumber);

                if (escapeNumber == correctEscapeNumber) {
                    printf("\nYou successfully escape the graveyard!\n");
                    return;
                } else {
                    printf("\nThe skeletons block your escape, forcing you to fight!\n");
                }
                break;
            }

            default:
                printf("\nInvalid choice! The skeletons take advantage of your hesitation!\n");
                break;
        }

        // Skeletons' turn to attack
        printf("\nThe skeletons attack!\n");
        for (int i = 0; i < 3; i++) {
            if (skeletons[i].isAlive) {
                printf("%s attacks you for 10 damage!\n", skeletons[i].name);
                player->health -= 10;
                if (player->health <= 0) {
                    printf("\nYou have been defeated by the skeletons. Game Over.\n");
                    exit(0);
                }
            }
        }
    }

    printf("\nYou have defeated all the skeletons!\n");
    printf("The graveyard grows silent, but you can feel the dark presence of the Lich deeper within...\n\n");
    // Next step: Lich encounter or exploration of the graveyard
}

void explorePath(Player *player) {
    int choice;

    printf("\nYou get to the fork in the road.\n\n");
    printf("1. Take the North path, which looks dark and narrow.\n\n");
    printf("2. Take the East path, where you can hear some running water.\n\n");
    printf("3. Take the South path, which looks well worn.\n\n");
    printf("What do you choose? ");
    scanf("%d", &choice);

    if (choice == 2) {
        riverCrossing(player);
    } else if (choice == 1) {
        caveEncounter(player);
    } else if (choice == 3) {
        farmersField(player);
    } else {
        printf("\nInvalid choice. Try again.\n\n");
    }
}

void riverCrossing(Player *player) {
    int choice;

    printf("\nYou reach a fast-flowing river.\n\n");
    printf("1. Try to swim across.\n\n");
    printf("2. Look for a bridge or some rocks to cross on.\n\n");
    printf("What do you choose? ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nThe river is too strong! You struggle to stay afloat.\n\n");
        player->health -= 20;
        printf("You lose 20 health. Current health: %d\n\n", player->health);
    } else if (choice == 2) {
        printf("\nYou find a fallen tree bridging the river and carefully cross over.\n\n");
    } else {
        printf("\nInvalid choice. You lose your way and wander back to the forest entrance.\n\n");
    }

    explorePath(player);
}

void caveEncounter(Player *player) {
    Enemy goblin = {"Goblin", 30, 1};
    Room cave = {
        .name = "Ancient Cave",
        .description = "a weathered stone door in the shape of a circle. Looks like it hasn't been open in ages",
        .item = "Ancient Amulet",
        .hasItem = 1,
        .locked = 1
    };
    
   struct NPC soldier = {
    .name = "Wounded Knight",
    .dialogue = "I was part of an elite squad tasked with defeating the Lich King in the graveyard across that river. My companions... they didn't make it. Will you do what we could'nt, and kill the lich?",
    .hasQuest = 1
};

    int choice;
    printf("\nYou arrive at the cave entrance. The air grows colder here, and a small campfire casts shadows on the ancient stone walls. Beside it sits a wounded knight, his armor bearing the crest of the Royal Guard.\n\n");

    do {
        printf("What would you like to do?\n\n");
        printf("1. Examine the cave entrance\n");
        printf("2. Speak with the wounded knight\n");
        printf("3. Open inventory\n");
        printf("4. Return to the previous path\n\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou approach the entrance, you see %s\n\n", cave.description);
                if (cave.locked) {
                    printf("The door is sealed by a overgrown lock. Perhaps a special key would help?\n\n");
                    unlockRoom(player, &cave);
                    if (!cave.locked) {
                        printf("The lock falls off as the door slowly opens, revealing a dark passage beyond.\n\n");
                        printf("Do you wish to enter? (1 for Yes, 2 for No): ");
                        int enterChoice;
                        scanf("%d", &enterChoice);
                        if (enterChoice == 1) {
                            printf("\nYou step into the darkness...\n\n");
                            combat(player, &goblin);
                            if (cave.hasItem) {
                                pickUpItem(player, &cave);
                            }
                            
                            // After defeating the goblin and potentially getting the item
                            printf("\nDeeper in the cave, you find yourself in a dimly lit chamber.\n");
                            printf("What would you like to do?\n\n");
                            printf("1. Continue forward towards the bridge\n");
                            printf("2. Return to the cave entrance\n\n");
                            
                            int deeperChoice;
                            scanf("%d", &deeperChoice);
                            
                            if (deeperChoice == 1) {
                                oldLadyBridge(player);
                                return;
                            }
                        }
                    }
                }
                break;

            case 2:
            printf("You walk over to the campfire, it seems like he doesn't notice you\n");
                interactWithNPC(player, &soldier);
                printf("'Be warned, traveler. The Lich's power grows stronger with each soul he claims.'\n\n");
                break;

            case 3:
                printInventory(player);
                break;

            case 4:
                printf("\nYou decide to return to the forest path.\n\n");
                explorePath(player);
                return;

            default:
                printf("\nInvalid choice. Please choose again.\n\n");
        }
    } while (1);
    }

void bridgeEncounter(Player *player) {
    Enemy bridgeTroll = {"Bridge Troll", 50, 1};
    Room bridgeRoom = {
        .name = "Bridge Crossing",
        .description = "A pristine wooden bridge surrounded by a bright clearing.",
        .item = "Troll's Key",
        .hasItem = 1,
        .locked = 0
    };

    int choice;

    printf("\nYou step into a bright clearing as you come upon a pristine wooden bridge.\n");
    printf("The surrounding area is serene, but the air feels heavy with a sense of foreboding.\n\n");

    do {
        printf("What would you like to do?\n");
        printf("1. Inspect the bridge\n");
        printf("2. Cross the bridge quietly\n");
        printf("3. Look around the area\n");
        printf("4. Step onto the bridge\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou examine the bridge closely. It appears to be well-maintained, with sturdy wooden planks and strong ropes.\n");
                printf("However, there are faint signs of claw marks and scorch marks near the edges, hinting at danger.\n");
                break;

            case 2:
                printf("\nYou try to cross the bridge quietly, hoping to avoid any trouble.\n");
                printf("As you step onto the bridge, a massive figure emerges from beneath it! It's a Bridge Troll!\n");
                printf("The troll growls, \"Pay the toll or face my wrath!\"\n\n");
                goto TrollEncounter; // Proceed to the troll encounter
                break;

            case 3:
                printf("\nYou look around the area and notice some bushes and trees near the bridge.\n");
                printf("After searching for a moment, you find nothing of interest. The area seems clear.\n");
                break;

            case 4:
                printf("\nYou step onto the bridge cautiously.\n");
                printf("As you do, a massive figure emerges from beneath the bridge! It's a Bridge Troll!\n");
                printf("The troll growls, \"Pay the toll or face my wrath!\"\n\n");
                goto TrollEncounter; // Proceed to the troll encounter
                break;

            default:
                printf("\nInvalid choice. Please choose again.\n");
        }
    } while (choice != 4 && choice != 2);

TrollEncounter: // Label for the main troll encounter logic
    do {
        printf("What would you like to do?\n\n");
        printf("1. Fight the Bridge Troll\n");
        printf("2. Attempt to negotiate\n");
        printf("3. Try to flee\n\n");
        printf("Your choice: "\n);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou prepare to fight the troll on the narrow bridge!\n");
                combat(player, &bridgeTroll);
                if (!bridgeTroll.isAlive) {
                    printf("\nThe troll lets out a final roar before collapsing. You carefully step over its massive body.\n\n");

                    // Check if the troll has an item (the key) to collect
                    if (bridgeRoom.hasItem) {
                        pickUpItem(player, &bridgeRoom);
                        printf("\nYou found the Troll's Key on its body! It might be important later.\n\n");
                    } else {
                        printf("\nThe troll seems to have nothing of value left.\n\n");
                    }
                }
                return;

            case 2:
                printf("\nYou try to reason with the troll.\n");
                if (player->gold >= 20) {
                    printf("The troll considers your offer and says, \"Fine. 20 gold and I'll let you pass.\"\n");
                    printf("Do you want to pay the toll? (1 for Yes, 2 for No): ");
                    int payChoice;
                    scanf("%d", &payChoice);
                    if (payChoice == 1) {
                        player->gold -= 20;
                        printf("\nYou pay the toll and the troll steps aside, allowing you to pass.\n");
                        printf("Remaining gold: %d\n\n", player->gold);
                        return;
                    } else {
                        printf("\nThe troll snarls, \"Then you shall face my wrath!\"\n");
                        combat(player, &bridgeTroll);
                        if (!bridgeTroll.isAlive) {
                            printf("\nThe troll lets out a final roar before collapsing. You carefully step over its massive body.\n\n");

                            // Check if the troll has an item (the key) to collect
                            if (bridgeRoom.hasItem) {
                                pickUpItem(player, &bridgeRoom);
                                printf("\nYou found the Troll's Key on its body! It might be important later.\n\n");
                            } else {
                                printf("\nThe troll seems to have nothing of value left.\n\n");
                            }
                        }
                        return;
                    }
                } else {
                    printf("\nThe troll laughs at your empty pockets and attacks you!\n");
                    combat(player, &bridgeTroll);
                    if (!bridgeTroll.isAlive) {
                        printf("\nThe troll lets out a final roar before collapsing. You carefully step over its massive body.\n\n");

                        // Check if the troll has an item (the key) to collect
                        if (bridgeRoom.hasItem) {
                            pickUpItem(player, &bridgeRoom);
                            printf("\nYou found the Troll's Key on its body! It might be important later.\n\n");
                        } else {
                            printf("\nThe troll seems to have nothing of value left.\n\n");
                        }
                    }
                    return;
                }

            case 3:
                printf("\nYou attempt to flee across the bridge!\n");
                printf("Pick a number (1-3): ");
                int fleeNumber, correctFleeNumber;
                scanf("%d", &fleeNumber);
                correctFleeNumber = rand() % 3 + 1;
                if (fleeNumber == correctFleeNumber) {
                    printf("\nYou sprint past the troll and make it across the bridge safely!\n");
                    return;
                } else {
                    printf("\nThe troll blocks your escape and roars, \"Coward! Face me!\"\n");
                    combat(player, &bridgeTroll);
                    if (!bridgeTroll.isAlive) {
                        printf("\nThe troll lets out a final roar before collapsing. You carefully step over its massive body.\n\n");

                        // Check if the troll has an item (the key) to collect
                        if (bridgeRoom.hasItem) {
                            pickUpItem(player, &bridgeRoom);
                            printf("\nYou found the Troll's Key on its body! It might be important later.\n\n");
                        } else {
                            printf("\nThe troll seems to have nothing of value left.\n\n");
                        }
                    }
                    return;
                }

            default:
                printf("\nInvalid choice. The troll glares at you menacingly.\n");
        }
    } while (1);
}


void mountainsEncounter(Player *player) {
    int choice;
    int dragonAwake = 0; // Track if the dragon wakes up (0 = sleeping, 1 = awake)

    printf("\nYou climb the steep, rocky path into the towering mountains. The air grows thin and cold as you ascend.\n");
    printf("At the peak, you discover a magnificent cave glittering with gems of every color. The walls seem to glow softly, illuminated by the faint light filtering in.\n");
    printf("In the center of the cavern lies a massive Crystal Dragon, its scales shimmering like diamonds. It is sleeping soundly, but its presence fills the air with an aura of power.\n\n");

    do {
        printf("What would you like to do?\n");
        printf("1. Examine the surroundings\n");
        printf("2. Attempt to steal a gem from the lair\n");
        printf("3. Try to sneak past the dragon\n");
        printf("4. Walk down the northern path\n");
        printf("5. Leave the mountain quietly\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou take a closer look at the cavern.\n");
                printf("The walls are encrusted with precious gems, and in the far corner, you spot a large golden chest partially hidden beneath rubble.\n");
                printf("The sleeping dragon occasionally lets out a soft growl, its claws twitching slightly in its slumber.\n\n");
                break;

            case 2: {
                printf("\nYou cautiously approach a cluster of glittering gems near the dragon.\n");
                printf("Your hands tremble as you reach out to grab one...\n");

                // Determine if the dragon wakes up (50% chance)
                int wakeChance = rand() % 2;
                if (wakeChance == 0) {
                    printf("\nYou manage to snatch a gem without waking the dragon! You quickly add it to your inventory.\n");
                    if (player->itemCount < MAX_INVENTORY_SIZE) {
                        strcpy(player->inventory[player->itemCount], "Crystal Gem");
                        player->itemCount++;
                    } else {
                        printf("Your inventory is full! You have to leave the gem behind.\n");
                    }
                } else {
                    printf("\nThe dragon stirs and opens its gleaming eyes, locking its gaze on you. The Crystal Dragon roars furiously, and the cavern trembles!\n");
                    dragonAwake = 1;
                }
                break;
            }

            case 3:
                printf("\nYou decide to sneak past the dragon and explore the far side of the lair.\n");

                // Determine if the dragon wakes up (50% chance)
                int sneakChance = rand() % 2;
                if (sneakChance == 0) {
                    printf("\nYou successfully sneak past the dragon and find a hidden passage leading deeper into the mountain.\n");
                    printf("You decide not to disturb the dragon further and quietly return to the entrance.\n");
                } else {
                    printf("\nThe dragon's eyes snap open as you accidentally knock over a small pile of gems. It rises, its crystalline wings spreading wide as it roars at you.\n");
                    dragonAwake = 1;
                }
                break;

            case 4:
                if (dragonAwake) {
                    printf("\nThe Crystal Dragon blocks your path, forcing you to deal with it before leaving.\n");
                } else {
                    printf("\nYou carefully leave the lair and head down the northern path.\n");
                    printf("The path leads you to a lush valley below, filled with mysterious flora and fauna. Your journey continues...\n\n");
                    return; // Exit the encounter
                }
                break;

            case 5:
                printf("\nYou decide to leave the mountain quietly and return to where you started.\n");
                explorePath(player); // Go back to the general exploration function
                return;

            default:
                printf("\nInvalid choice. Please choose again.\n");
        }

        // If the dragon wakes up
        if (dragonAwake) {
            printf("\nThe Crystal Dragon stands before you, its glowing scales pulsing with power.\n");
            printf("Its voice booms, \"WHO DARES TO DISTURB MY SLUMBER?\"\n");

            printf("\nWhat will you do?\n");
            printf("1. Apologize and beg for mercy\n");
            printf("2. Offer gold to appease the dragon\n");
            printf("3. Attempt to fight the dragon\n");
            printf("4. Flee the lair\n");
            printf("Your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("\nYou fall to your knees and apologize profusely.\n");
                    printf("The dragon stares at you for a moment before huffing, \"LEAVE, AND NEVER RETURN.\"\n You quickly retreat down the mountain.\n");
                    return;

                case 2:
                    printf("\nYou offer the dragon 50 gold in hopes of appeasing its wrath.\n");
                    if (player->gold >= 50) {
                        player->gold -= 50;
                        printf("The dragon snorts, \"A MEAGER GIFT, BUT ACCEPTABLE. NOW BE GONE.\"\n");
                        printf("You carefully retreat down the mountain. Remaining gold: %d\n", player->gold);
                        return;
                    } else {
                        printf("The dragon roars, \"YOU DARE OFFER ME NOTHING?\" It prepares to attack!\n");
                        combat(player, &(Enemy){"Crystal Dragon", 100, 1});
                    }
                    break;

                case 3:
                    printf("\nYou prepare to fight the Crystal Dragon!\n");
                    combat(player, &(Enemy){"Crystal Dragon", 100, 1});
                    if (player->health > 0) {
                        printf("\nYou have defeated the Crystal Dragon! Its body shatters into shards of crystal, leaving behind a massive gem.\n");
                        if (player->itemCount < MAX_INVENTORY_SIZE) {
                            strcpy(player->inventory[player->itemCount], "Dragon Crystal");
                            player->itemCount++;
                        } else {
                            printf("Your inventory is full! You leave the crystal behind.\n");
                        }
                        printf("\nWith the dragon defeated, you explore the lair and find a treasure chest filled with gold.\n");
                        player->gold += 200;
                        printf("You receive 200 gold! Current gold: %d\n", player->gold);
                    } else {
                        printf("\nThe Crystal Dragon has defeated you. Game Over.\n");
                        exit(0);
                    }
                    return;

                case 4:
                    printf("\nYou attempt to flee, but the dragon roars and chases after you!\n");
                    combat(player, &(Enemy){"Crystal Dragon", 100, 1});
                    break;

                default:
                    printf("\nInvalid choice. The dragon looms over you menacingly.\n");
            }
        }
    } while (1);
}


void oldLadyBridge(Player *player) {
    int choice;
    struct NPC oldLady = {
        .name = "Old Lady",
        .dialogue = "Ah, traveler, you seem brave enough to face the dangers of this land. Beware, for the mountains hold a fearsome dragon. And just up ahead is the lich king, he kills anyone in his path, be carful.",
        .hasQuest = 0 // No quest from the old lady
    };

    printf("\nYou approach a rickety wooden bridge swaying gently in the wind. Standing at the center is a frail old woman wrapped in a tattered cloak.\n");
    printf("As you near her, she gazes at you with piercing, wise eyes.\n\n");

    do {
        printf("What would you like to do?\n");
        printf("1. Talk to the old lady\n");
        printf("2. Cross the bridge silently\n");
        printf("3. Turn back\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou approach the old lady.\n");
                interactWithNPC(player, &oldLady);
                printf("She smiles faintly and adds, \"Good luck, brave traveler.\"\n\n");
                break;

            case 2:
                printf("\nYou decide to cross the bridge silently, nodding politely to the old lady as you pass.\n");
                printf("Her voice follows you: \"Remember, not all battles are won by strength alone.\"\n");
                printf("\nYou make it across the bridge safely.\n\n");
                graveyardEncounter(player);
                return;

            case 3:
                printf("\nYou decide to turn back, feeling unprepared for what lies ahead.\n");
                return;

            default:
                printf("\nInvalid choice. Please choose again.\n");
        }
    } while (1);
}

void combat(Player *player, Enemy *enemy) {
    if (!enemy->isAlive) {
        printf("\nThe %s is already dead.\n\n", enemy->name);
        return;
    }
    
    printf("\nA %s lunges from the shadows! It has %d health.\n\n", enemy->name, enemy->health);
    int escapeNumber, dodgeNumber, playerChoice;

    while (enemy->isAlive && player->health > 0) {
        printf("\nCombat Options:\n");
        printf("1. Attack\n");
        printf("2. Open Inventory\n");
        printf("3. Block\n");
        printf("4. Attempt Escape\n\n");
        printf("What will you do? ");
        scanf("%d", &playerChoice);

        switch (playerChoice) {
            case 1: // Attack
                printf("\nYou strike at the %s!\n", enemy->name);
                enemy->health -= 20;
                printf("The %s has %d health remaining!\n\n", enemy->name, enemy->health);
                
                if (enemy->health <= 0) {
                    printf("You have slain the %s!\n\n", enemy->name);
                    enemy->isAlive = 0;
                    return;
                }
                break;

            case 2: // Inventory
                while (1) {
                    printInventory(player);
                    if (player->itemCount > 0) {
                        printf("\nEnter item number to use (0 to return to combat): ");
                        int itemChoice;
                        scanf("%d", &itemChoice);
                        
                        if (itemChoice == 0) break;
                        
                        if (itemChoice > 0 && itemChoice <= player->itemCount) {
                            itemChoice--; // Adjust for 0-based array
                            
                            // Item usage logic
                            if (strcmp(player->inventory[itemChoice], "Health Potion") == 0) {
                                player->health += 20;
                                printf("\nYou drink the Health Potion. Health restored to %d!\n", player->health);
                                // Remove used item
                                for (int i = itemChoice; i < player->itemCount - 1; i++) {
                                    strcpy(player->inventory[i], player->inventory[i + 1]);
                                }
                                player->itemCount--;
                                break;
                            }
                            else if (strcmp(player->inventory[itemChoice], "Damage Potion") == 0) {
                                enemy->health -= 50;
                                printf("\nYou throw the Damage Potion! The %s takes 50 damage!\n", enemy->name);
                                if (enemy->health <= 0) {
                                    printf("The %s has been defeated!\n\n", enemy->name);
                                    enemy->isAlive = 0;
                                    return;
                                }
                                // Remove used item
                                for (int i = itemChoice; i < player->itemCount - 1; i++) {
                                    strcpy(player->inventory[i], player->inventory[i + 1]);
                                }
                                player->itemCount--;
                                break;
                            }
                            else if (strcmp(player->inventory[itemChoice], "Apple") == 0) {
                                player->health += 5;
                                printf("\nYou quickly eat the Apple. Health restored to %d!\n", player->health);
                                // Remove used item
                                for (int i = itemChoice; i < player->itemCount - 1; i++) {
                                    strcpy(player->inventory[i], player->inventory[i + 1]);
                                }
                                player->itemCount--;
                                break;
                            }
                        }
                    } else {
                        printf("\nPress 0 to return to combat: ");
                        int temp;
                        scanf("%d", &temp);
                        if (temp == 0) break;
                    }
                }
                continue; // Skip enemy turn after inventory management

            case 3: // Block
                printf("\nYou raise your guard, ready to block the next attack!\n");
                break;

            case 4: // Escape
                printf("\nYou attempt to escape!\n");
                printf("Pick a number (1-3): ");
                scanf("%d", &escapeNumber);
                
                int correctEscapeNumber = rand() % 3 + 1;
                
                if (escapeNumber == correctEscapeNumber) {
                    printf("\nYou successfully escape from the battle!\n\n");
                    return;
                } else {
                    printf("\nEscape failed! The %s blocks your path!\n\n", enemy->name);
                }
                break;

            default:
                printf("\nInvalid choice! The %s takes advantage of your hesitation!\n", enemy->name);
                break;
        }

        // Enemy turn
        if (enemy->isAlive) {
            printf("\nThe %s prepares to attack!\n", enemy->name);
            printf("Try to dodge! Pick a number (1-2): ");
            scanf("%d", &dodgeNumber);
            
            int correctDodgeNumber = rand() % 2 + 1;
            
            if (dodgeNumber == correctDodgeNumber) {
                printf("\nYou successfully dodge the attack!\n\n");
            } else {
                int damage = (playerChoice == 3) ? 0 : 15; // No damage if blocked
                if (playerChoice == 3) {
                    printf("\nYou successfully block the attack!\n\n");
                } else {
                    player->health -= damage;
                    printf("\nThe attack hits! You take %d damage!\n", damage);
                    printf("You have %d health remaining.\n\n", player->health);
                }
            }
        }

        if (player->health <= 0) {
            printf("\nYou have been defeated by the %s. Game Over.\n\n", enemy->name);
            exit(0);
        }
    }
}

void printInventory(Player *player) {
    if (player->itemCount == 0) {
        printf("\nYour inventory is empty.\n\n");
    } else {
        printf("\nYour inventory:\n\n");
        for (int i = 0; i < player->itemCount; i++) {
            printf("- %s\n\n", player->inventory[i]);
        }
    }
}

void pickUpItem(Player *player, Room *room) {
    if (room->hasItem) {
        if (player->itemCount < MAX_INVENTORY_SIZE) {  // Use MAX_INVENTORY_SIZE instead of MAX_INVENTORY
            strcpy(player->inventory[player->itemCount], room->item);
            player->itemCount++;
            printf("\nYou picked up %s\n", room->item);
            room->hasItem = 0;
            room->item[0] = '\0';  // Clear the item
        } else {
            printf("\nYour inventory is full!\n");
        }
    } else {
        printf("\nThere is nothing to pick up here.\n");
    }
}

void interactWithNPC(Player *player, struct NPC *npc) {
    printf("\n%s says: %s\n", npc->name, npc->dialogue);
    
    if (npc->hasQuest) {
        if (!npc->quest.isActive && !npc->quest.isCompleted) {
            printf("\nWill you accept this quest? (1: Yes, 2: No): ");
            int choice;
            scanf("%d", &choice);
            
            if (choice == 1) {
                // Initialize quest details only after player accepts
                npc->quest = (struct Quest){
                    .isActive = 1,
                    .isCompleted = 0,
                    .rewardGold = 150,
                };
                strcpy(npc->quest.targetItem, "Lich's Head");
                strcpy(npc->quest.description, "Defeat the Lich King and bring back his head as proof");
                
                printf("\nQuest accepted: %s\n", npc->quest.description);
                printf("Reward: %d gold\n", npc->quest.rewardGold);
            }
        }
        else if (npc->quest.isActive && !npc->quest.isCompleted) {
            // Check if player has the Lich's Head
            for (int i = 0; i < player->itemCount; i++) {
                if (strcmp(player->inventory[i], "Lich's Head") == 0) {
                    printf("\nYou present the Lich's Head to the wounded knight.\n");
                    printf("'You... you actually did it! The realm is safer thanks to your bravery.'\n");
                    
                    // Remove the Lich's Head from inventory
                    for (int j = i; j < player->itemCount - 1; j++) {
                        strcpy(player->inventory[j], player->inventory[j + 1]);
                    }
                    player->itemCount--;
                    
                    // Give reward
                    player->gold += npc->quest.rewardGold;
                    printf("\nReceived %d gold!\n", npc->quest.rewardGold);
                    printf("Current gold: %d\n", player->gold);
                    
                    npc->quest.isCompleted = 1;
                    npc->quest.isActive = 0;
                    strcpy(npc->dialogue, "Thank you for defeating the Lich King. The realm is in your debt.");
                    return;
                }
            }
            printf("\n'Remember, bring me the Lich's Head as proof of your victory.'\n");
        }
        else if (npc->quest.isCompleted) {
            printf("\nThe knight nods at you with respect.\n");
        }
    }
}

void farmersField(Player *player) {
    int choice;

    // Initialize the old man as an NPC with a quest
    struct NPC oldMan = {
        .name = "Old Farmer",
        .dialogue = "Hello traveler! I need your help. A troll has stolen a key I was entrusted with by a knight. Please, retrieve it for me!",
        .hasQuest = 1,
        .quest = {
            .isActive = 0,
            .isCompleted = 0,
            .rewardGold = 50,
        }
    };
    strcpy(oldMan.quest.targetItem, "Troll's Key");
    strcpy(oldMan.quest.description, "Retrieve the key stolen by the troll and return it to the old farmer.");

    printf("\nYou are standing in front of a farm.\n");
    printf("An old man is trying to get your attention.\n");

    do {
        printf("\nWhat would you like to do?\n");
        printf("1. Walk over and listen to what he has to say.\n");
        printf("2. Continue on your journey and ignore the man in need.\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Interact with the old man
            printf("\nYou approach the old farmer.\n");
            interactWithNPC(player, &oldMan);

            // If the player accepts the quest
            if (oldMan.quest.isActive && !oldMan.quest.isCompleted) {
                printf("\nThe farmer says: \"The troll lives in a cave near the river to the east. Be careful, traveler!\"\n");
                printf("You now have an active quest: %s\n", oldMan.quest.description);
                return;
            }

            // If the player has already completed the quest
            if (oldMan.quest.isCompleted) {
                printf("\nThe farmer smiles warmly: \"Thank you, traveler, for retrieving the key. Here's your reward!\"\n");
                player->gold += oldMan.quest.rewardGold;
                printf("You received %d gold. Current gold: %d\n", oldMan.quest.rewardGold, player->gold);
                oldMan.hasQuest = 0;  // No more quests from this NPC
                return;
            }
        } else if (choice == 2) {
            // Continue the journey without helping
            printf("\nYou decide to leave the farmer behind and continue on your path.\n");
            bridgeEncounter(player);
            return;
        } else {
            // Invalid input
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 1 && choice != 2);
}

void unlockRoom(Player *player, Room *room) {
    if (room->locked) {
        for (int i = 0; i < player->itemCount; i++) {
            if (strcmp(player->inventory[i], "Secret Key") == 0) {
                room->locked = 0;
                printf("\nYou used the Secret Key to unlock the %s.\n\n", room->name);
                return;
            }
        }
        printf("\nYou don't have the key to unlock the %s.\n\n", room->name);
    } else {
        printf("\nThe %s is already unlocked.\n\n", room->name);
    }
}

void checkActiveQuests(Player *player, struct NPC *npc) {
    if (npc->quest.isActive) {
        printf("\nActive Quest: %s\n", npc->quest.description);
        printf("Reward: %d gold\n", npc->quest.rewardGold);
    }
}
