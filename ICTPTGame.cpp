// PT
// Naidas, Rubio, Addatu, Santos, Humarang - S12G

#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <chrono>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int idx = 7) { SetConsoleTextAttribute(h, idx); }

bool active = true;
int retry_code = -1;
string pname = "";

void print(string text = "", int color_idx = 7) { color(color_idx); cout << text << "\n"; color(); }

void err(string text = "") { print("ERR: " + text, 4); }

void separator(int n = 15, string s = "=") {
	string a; for (int i = 0; i < n; i++) { a += s; }
	cout << "\n" << a << "\n";
}

class Human {
	private:
		const int MAX_HP = 100;
		const int MAX_ST = 50;
		const int MAX_FU = 50;

	public:
		//Human& self = *this;
	
		int hp = 100; // health
		int st = 50; // energy
		int fu = 20; // hunger
		int atk = 10;

		string name = "unknown";

		void inc_stat(int& stat, int inc, int max_val) { stat = max(0, min(max_val, stat + inc)); print(); }

		void state_inc(int inc, string positive, string negative, string unit) { bool c = (inc >= 0); print(name + (c ? positive : negative) + to_string(inc) + " " + unit, (c ? 10 : 4) ); }
		
		//void bar_view(int val, int max_val, string name) { cout << name << " BAR : |[[ "; for (int i = 0 ; i < max_val ; i++ ) { cout << ((i < val) ? "X" : "_"); } cout << " ]]|\n\n"; }
		void bar_num(int val, int max_val, string name) { cout << name + ": " + to_string(val) + "/" + to_string(max_val) << "\n"; }

		void inc_hp(int inc) { hp = min(hp + inc, MAX_HP); state_inc(inc, " was healed +", " was hurt ", "HP"); bar_hp(); }
		void inc_st(int inc) { if (st <= 0 && inc < 0) { st_to_dmg(inc); } inc_stat(st, inc, MAX_ST); state_inc(inc, " had rested +", " has been tired ", "ST"); bar_st(); }
		void inc_fu(int inc) { inc_stat(fu, inc, MAX_FU); state_inc(inc, " was fed +", " got hungry ", "FU"); bar_fu(); }

		void bar_hp() { bar_num(hp, MAX_HP, "HEALTH"); }
		void bar_st() { bar_num(st, MAX_ST, "STAMINA"); }
		void bar_fu() { bar_num(fu, MAX_FU, "FULLNESS"); }

		void hurt(int dmg, string attacker_name, bool p = true) {
			if (p) { print(attacker_name + " attacked " + name); }
			inc_hp(dmg);
		}

		void st_to_dmg(int inc = 0) { inc_hp(int(inc * 0.5)); }

		Human(string _name, int ihp = 100, int ist = 50, int ifu = 20, int iatk = 10) {
			name = _name; hp = ihp; st = ist; fu = ifu; atk = iatk;
			
		}
};

class Zombie: public Human {
	public:
		
		void bite(Human& human) {
			print("\n << Zombie " + name + " attacked " + human.name + " >>");
			human.hurt(-atk, name, false);
		}

		Zombie(string _name, int iatk = 10, int ihp = 100, int ist = 50, int ifu = 20)
			: Human(_name, ihp, ist, ifu, iatk) {
			
		}

		
};

string rando_zombie_name() {
	// randomization
	static mt19937 gen([]() {
		random_device rd;
		auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
		seed_seq seq{
			rd(),
			static_cast<unsigned int>(now),
			static_cast<unsigned int>(now >> 32)
		};
		return mt19937(seq);
	}());
	uniform_int_distribution<int> int_dist(0, 9);
	int r_int = int_dist(gen); // random number

	string zombie_names[10] = { "Mio", "Drei", "Reyjen", "Rance", "Santi", "Magnus", "Matteo", "Willard", "Macky", "Samy" };
	return zombie_names[r_int];
}

void general_print(string header = "HEADER", string text = "text", int hci = 7, int tci = 7, int sl = 15, string ss = "=") {
	separator(sl, ss); print();
	print("=== " + header + " ===\n", hci);
	print(text, tci);
	separator(sl, ss);
	print();
}

void input_pause() { print("Input '0' to proceed."); int buffer; cin >> buffer; }

void query_print(string header = "decision", string text = "result") { general_print( header, text, 9, 7, 15, "-" ); }

void decision_print(int& php, string header = "decision", string text = "result") { if (php <= 0) { return; } general_print( header, text, 8, 7, 10, "-" ); input_pause(); }

int chapter = 0;

void setup() {
	int choice = -1; // inputbuffer n selection
	while (choice == -1 || chapter == 0) {
		print();
		general_print(
			"3 DAYS BEFORE RESCUE",
			"1 - START\n2 - TUTORIAL\n3 - EXIT",
			3,
			7,
			30
		);
		
		cin >> choice;
		switch (choice) {
			case 1:
				chapter = 1;
				break;
			case 2:
			
				separator();

				general_print(
					"OBJECTIVE",
					"Your mission is to survive for three days until the rescue team arrives. Make smart decisions to avoid danger and stay alive.",
					7, 8, 3, "-"
				);

				general_print(
					"PLAYER ATTRIBUTES",
					"You have three survival attributes:\nHEALTH - Represents your physical condition and life. (100 HP)\nSTAMINA - Represents your energy and ability to perform activities. If the stamina bar is zero and there's stamina deduction, it gets converted to HP damage. (50 ST)\nHUNGER - Represents your ability to stay nourished. (20 FU)",
					7, 8, 3, "-"
				);

				general_print(
					"DECISION MAKING",
					"Each scene presents a situation with multiple choices. Read the scenario carefully and select the option you think is best. Wrong choices lead to a deduction of points from either Health, Stamina, and/or Hunger.",
					7, 8, 3, "-"
				);

				general_print(
					"GAME OVER CONDITION",
					"If health reaches zero, the player dies. If hunger reaches zero, 5 health points are deducted per-next scenario. If stamina reaches zero, certain strenuous actions cannot be performed which may lead to deduction of health points.",
					7, 8, 3, "-"
				);

				general_print(
					"MULTIPLE ENDINGS",
					"Your decisions determine your fate. Survive until the rescue team arrives to complete your mission. You may also encounter different endings depending on your actions.",
					7, 8, 3, "-"
				);

				separator();

				print("\nGOOD LUCK, SURVIVOR!\nRemember, every decision matters. Choose wisely, manage your points, and stay alive!\n");
				
				input_pause();

				choice = -1;
				break;
			case 3:
				active = false;
				chapter = -2;
				retry_code = -1;
				pname = "";
				return;
			default:
				err("Enter a valid index.");
				cin.ignore(10000, '\n');
				chapter = 0;
				break;
		}
	}

	

}

string choice_formatting(string desc, string c1, string c2, string c3) {
	return (desc + "\n\n1 - " + c1 + "\n2 - " + c2 + "\n3 - " + c3 + "\n\n");
}

int query_buffer() {
	int ib;
	while (true) {
		if (!(cin >> ib)) {
			cin.clear();
			cin.ignore(10000, '\n');
			err("Enter a valid choice.");
			continue;
		}
		if (ib > 0 && ib < 4) { return ib; }
		err("Enter a valid choice.");
		cin.ignore(10000, '\n');
	}
}

void gameplay(string _pname = "") {
	retry_code = -1;
	
	
	if (_pname == "") {
		setup();
		if (chapter != -2) {
			general_print(
				"Name your PLAYER",
				"Provide your vessel a name so that it may be referred to that way.",
				2, 8, 30, "-"
			);
			cin >> pname;
		}
	} else { // quick setup
		chapter = 1;
		pname = _pname;
	}

	

	Human player(pname);

	while (active) {
		switch (chapter) {
			case 1:
			
				// the beginning

				query_print(
					"October 24, 2026 - 6:30am",
					choice_formatting(
						"You, " + pname + ", wake up to the sound of screaming and alarms. You are one of five participants in an experimental study conducted by a scientist developing a potential cure for the Hantavirus. Unfortunately, the experiment failed for the other four participants. They developed severe neurological complications, became aggressive, and transformed into zombie-like creatures. You were the only successful subject.\n\n One of the infected escaped containment and attacked the facility's personnel, spreading the outbreak throughout the building. You hear footsteps and screams outside your room. Something is terribly wrong.\n\n What will you do?",
						"Peek through the hallway.", "Barricade your room.", "Immediately leave your room."
					)
				);

				switch (query_buffer()) {
					case 1: {
						player.inc_st(-5);
					
						decision_print(
							player.hp,
							"Peek through the hallway.",
							"You crack the door open just enough to see down the corridor. Two infected test subjects are tearing into a security guard at the far end, completely distracted. You slip out quietly into the opposite hallway, avoiding their notice."
						);

						break;
					}
					case 2: {
						Zombie z(rando_zombie_name(), 10);
						z.bite(player);
						player.inc_st(-15);

						decision_print(
							player.hp,
							"Barricade your room.",
							"You shove the heavy steel bedframe against the door, straining your muscles. Minutes later, an infected slams against the frame. The impact splinters the wood and sends sharp debris into your arm before you force your way out through a side bathroom window."
						);

						break;
					}

					case 3: {
						Zombie z(rando_zombie_name(), 25);
						z.bite(player);
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Immediately leave your room.",
							"You throw the door open and sprint straight into an infected researcher. It lunges at you, clawing deeply at your shoulder before you manage to shove it off and stumble down the stairwell."
						);

						break;
					//default:
						// theoretically it should never reach here due to query_buffer(), so just never add the default case
						//break;
					}
				}

				chapter = 2;

				break;

			case 2:
				
				// escaping the facility

				query_print(
					"October 24, 2026 - 6:50am",
					choice_formatting(
						"You discover that the air vent connects to the maintenance corridor. However, you hear infected individuals approaching. You need to escape quickly.\n\n Which route will you take?",
						"Crawl through the ventilation system.", "Run through the main hallway.", "Search the security office."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-10);
					
						decision_print(
							player.hp,
							"Crawl through the ventilation system.",
							"The metal ducts are tight and suffocating, but the infected cannot reach you. You crawl silently above the chaos and drop down safely right next to the unguarded maintenance exit."
						);

						break;
						
					case 2: {
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 30);
						z.bite(player);
						player.inc_st(-20);

						decision_print(
							player.hp,
							"Run through the main hallway.",
							"You sprint down the main corridor, but the automatic glass doors at the entrance are locked down. Cornered by three infected, you barely smash through a side window, taking heavy cuts and bites as you scramble outside."
						);

						break;

					}
					case 3: {
						
						Zombie z(rando_zombie_name(), 15);
						z.bite(player);
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Search the security office.",
							"You duck into the security office and grab a master keycard off the desk. Just as you turn to leave, a glass partition shatters, an infected lunges through, slashing your leg before you swipe the card and slam the heavy exit door shut behind you."
						);

						break;
					}
				}

				chapter = 3;

				break;

			case 3:
				
				// Supplies 

				query_print(
					"October 24, 2026 - 7:10am",
					choice_formatting(
						"You finally escape the research facility. The streets are filled with abandoned vehicles, scattered belongings, and distant screams.\n\n You need to find a safe place to spend the night and gather supplies. Where will you go?",
						"Abandoned Shed.", "Abandoned Vehicle.", "Convenience Store."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-5);
						player.inc_fu(15);
					
						decision_print(
							player.hp,
							"Abandoned Shed.",
							"The wooden shed is cramped and drafty, but quiet. You eat a can of beans, drink some water, and tune the old battery-powered radio to search for news while keeping watch through the cracks."
						);

						break;
						
					case 2: {
						Zombie z(rando_zombie_name(), 25);
						z.bite(player);
						player.inc_st(-15);
						player.inc_fu(5);

						decision_print(
							player.hp,
							"Abandoned Vehicle.",
							"You hotwire the car, and the engine roars to life, echoing down the empty street. Within seconds, a horde swarms the vehicle, smashing the driver's window and dragging you out before you barely escape on foot into a nearby alley."
						);

						break;
					}
					case 3:
						
						player.inc_st(-5);
						player.inc_fu(25);

						decision_print(
							player.hp,
							"Convenience Store.",
							"You pull down the metal security shutters and lock the front doors. Inside, you find untouched shelves of food, bottled water, medical supplies, and a portable radio behind the counter. You are safe for the night."
						);

						break;
				}

				chapter = 4;

				break;

			case 4:

				// emergency broadcast 

				query_print(
					"October 24, 2026 - 8:00pm",
					"After securing your shelter, you turn on the radio and search for an emergency broadcast. Suddenly, a government announcement interrupts the static. The message confirms that a major outbreak has spread throughout the area. Rescue teams are being organized, but evacuation will only begin in three days.\n\n The announcement also advises survivors to stay indoors, conserve their supplies, and avoid contact with infected individuals. You realize that help will not arrive immediately. You must survive two more days before rescue.\n\n You lock the doors, organize the supplies you collected, and prepare to face another day."
				);
				
				player.inc_st(20);
				
				separator(); print();

				print("DAY ONE - SURVIVED");

				player.bar_hp(); player.bar_st(); player.bar_fu();
				
				separator(); print();

				input_pause();

				chapter = 5;

				break;

			case 5:
				
				// A New Morning

				query_print(
					"October 25, 2026 - 7:00am",
					choice_formatting(
						"You wake up after a restless night. The emergency broadcast repeats that rescue operations are still three days away, but supplies are running low. While checking the radio, you hear an announcement that the nearest hospital may still have medical supplies and emergency equipment.\n\n You decide to head there. Before leaving, you prepare your belongings and plan your route. The streets are still dangerous, and you cannot afford to make careless decisions.\n\n How will you travel to the hospital?",
						"Take the Main Road.", "Use the Back Alleys.", "Pass Through the Public Market."
					)
				);

				switch (query_buffer()) {
					case 1: {
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 25);
						player.inc_st(-15);
					
						decision_print(
							player.hp,
							"Take the Main Road.",
							"The open highway leaves you completely exposed. Halfway to the hospital, a pack of infected spots you from behind a pileup of wrecked cars, forcing you into a brutal, exhausting brawl just to break free."
						);

						break;
					}
					case 2:
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Use the Back Alleys.",
							"Moving from shadow to shadow through narrow service alleys takes longer, but you bypass the main hordes entirely and reach the hospital's rear loading dock without being seen."
						);

						break;

					case 3: {
						
						Zombie z(rando_zombie_name() + ", and " + rando_zombie_name(), 15);
						player.inc_st(-15);
						player.inc_fu(20);

						decision_print(
							player.hp,
							"Pass Through the Public Market.",
							"You scavenge packaged food and water from overturned stalls, but knocking over a metal crate alerts two infected wandering the aisles. You take a nasty hit to the ribs before vaulting over a fence toward the hospital."
						);

						break;
					}
				}

				chapter = 6;

				break;


			case 6:
				
				// Inside the Hospital

				query_print(
					"October 25, 2026 - 10:30am",
					choice_formatting(
						"You arrive at the hospital and find the entrance partially damaged. Several rooms have been abandoned, and medical supplies are scattered across the floor. You hear movement coming from the emergency wing.\n\n You need to find useful supplies without putting yourself in unnecessary danger. Where will you search?",
						"Enter the Pharmacy.", "Search the Emergency Ward.", "Go to the Hospital Laboratory."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_hp(20);
						player.inc_st(-5);
					
						decision_print(
							player.hp,
							"Enter the Pharmacy.",
							"You quietly jimmy the pharmacy door open. Most of the narcotics are gone, but you find antiseptic, bandages, and antibiotics on the lower shelves, enough to clean and dress your wounds."
						);

						break;
						
					case 2: {
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 30);
						z.bite(player);
						player.inc_st(-15);

						decision_print(
							player.hp,
							"Search the Emergency Ward.",
							"The emergency ward is a nightmare. Several patients strapped to gurneys have turned and break free as you walk past, lunging at you in the dark before you fight your way back into the lobby."
						);

						break;
					}

					case 3: {
						
						Zombie z(rando_zombie_name(), 10);
						z.bite(player);
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Go to the Hospital Laboratory.",
							"Using your instincts, you slip into the restricted lab and grab early blood-test logs on the Hantavirus mutation. A stray infected lab technician corners you near the exit, forcing you to take a blow while escaping."
						);

						break;
					}
				}

				chapter = 7;

				break;

			case 7:

				// Unexpected Discovery

				query_print(
					"October 25, 2026 - 1:00pm",
					choice_formatting(
						"After gathering supplies, you discover a computer in the hospital records room. It contains an emergency report about the outbreak. According to the document, the infected individuals were former participants in an experimental treatment conducted at a nearby research facility.\n\n You recognize the details from the experiment you survived. The report also mentions that an evacuation point has been established in a nearby suburb.\n\n Before leaving, you hear a loud crash from the hallway. Someone or something is approaching. What will you do?",
						"Download the Emergency Report.", "Immediately Leave the Hospital.", "Investigate the Noise."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-5);
					
						decision_print(
							player.hp,
							"Download the Emergency Report.",
							"Your hands shake as the progress bar hits 100%. You pocket the flash drive containing the suburb evacuation map and slip out the fire exit just as a pair of infected bursts through the main doors."
						);

						break;
						
					case 2:
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Immediately Leave the Hospital.",
							"You don't take any chances, you bolt out the nearest stairwell and sprint into the parking lot. You escape unharmed, though you missed crucial details about the outbreak."
						);

						break;

					case 3: {
						
						Zombie z("Big Chonggo", 35);
						z.bite(player);
						player.inc_st(-15);

						decision_print(
							player.hp,
							"Investigate the Noise.",
							"Hoping to find another survivor, you round the corner, only to come face-to-face with a hulking, mutated test subject. It hurls you into a wall before you barely crawl away down the emergency stairs."
						);

						break;
					}
				}

				chapter = 8;

				break;

			case 8:
				
				// Preparing for the final day

				query_print(
					"October 25, 2026 - 6:00pm",
					"You manage to escape the hospital with the information and supplies you gathered. Through the radio, you hear another emergency announcement confirming that rescue teams will begin evacuating survivors from the designated point in the suburb tomorrow. You now know where you need to go. However, reaching the evacuation point will not be easy. You find a temporary hiding place near the hospital and prepare for the final day."
				);

				player.inc_st(25);

				separator(); print();

				print("DAY TWO - SURVIVED");

				player.bar_hp(); player.bar_st(); player.bar_fu();
				
				separator(); print();

				input_pause();
				
				chapter = 9;

				break;

			case 9:
				
				// the final morning

				query_print(
					"October 26, 2026 - 6:00am",
					choice_formatting(
						"You wake up to the sound of distant explosions and emergency sirens. The radio announces that rescue teams will arrive at the designated evacuation point in the suburb later today. Survivors must reach the area before the rescue operation ends.\n\n You gather the supplies you have left and prepare to leave. This is your final chance to escape the outbreak. How will you get to the evacuation point?",
						"Travel Through the Main Highway.", "Use the Residential Streets.", "Cross the Nearby Construction Site."
					)
				);

				switch (query_buffer()) {
					case 1: {
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 25);
						player.inc_st(-15);
					
						decision_print(
							player.hp,
							"Travel Through the Main Highway.",
							"Military barricades and burned-out trucks trap you straight into a chokepoint swarming with infected. You have to fight tooth and nail to climb over the wreckage and reach the suburb."
						);

						break;
					}
					case 2:
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Use the Residential Streets.",
							"Cutting through quiet cul-de-sacs and tree-lined yards keeps you out of sight. You conserve your energy and reach the edge of the suburb safely."
						);

						break;

					case 3:
						
						player.inc_hp(-15);
						player.inc_st(-20);

						decision_print(
							player.hp,
							"Cross the Nearby Construction Site.",
							"The shortcut saves time, but rusted scaffolding collapses beneath your weight. You fall hard onto concrete, bruising your ribs and draining your stamina before limping out the other side."
						);

						break;
				}

				chapter = 10;

				break;

			case 10:
				
				// the blocked neighborhood

				query_print(
					"October 26, 2026 - 10:00am",
					choice_formatting(
						"You arrive at the suburb, but the streets are unusually quiet. Several houses have been abandoned, and a damaged vehicle blocks the road ahead. You hear infected individuals approaching from behind.\n\n You need to find a way through the neighborhood without getting surrounded. What will you do?",
						"Enter an Abandoned House.", "Push the Damaged Vehicle Aside.", "Run Through the Main Street."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-5);
						player.inc_fu(10);
					
						decision_print(
							player.hp,
							"Enter an Abandoned House.",
							"You slip quietly through an unlocked back door, grab a stray energy bar from the kitchen counter, and hop the backyard fence into the next street, leaving the infected wandering aimlessly behind you."
						);

						break;
						
					case 2: {
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 30);
						player.inc_st(-25);

						decision_print(
							player.hp,
							"Push the Damaged Vehicle Aside.",
							"The metal screeches loudly against the asphalt as you strain to move the wreck. Drawn by the noise, a dozen infected sprint down the street and overwhelm you before you can break away."
						);

						break;
					}
					case 3:
						
						player.inc_hp(-10);
						player.inc_st(-20);

						decision_print(
							player.hp,
							"Run Through the Main Street.",
							"You vault over the car hood and sprint at full speed. Infected chase you for three blocks, grazing your back before you finally lose them around a sharp corner."
						);

						break;
				}

				chapter = 11;

				break;

			case 11:
				
				// the last obstacle

				query_print(
					"October 26, 2026 - 1:00pm",
					choice_formatting(
						"You finally reach the area near the evacuation point. However, a large group of infected individuals has gathered around the entrance. You can hear rescue vehicles in the distance, which means the evacuation operation may begin soon.\n\n You must find a safe way to reach the rescue team. What will you do?",
						"Use the Nearby Service Entrance.", "Create a Distraction.", "Force Your Way Through the Crowd."
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-5);
					
						decision_print(
							player.hp,
							"Use the Nearby Service Entrance.",
							"You circle behind the community center and slip through an unguarded maintenance door. Within moments, you emerge inside the fortified perimeter where armed soldiers wave you toward the extraction vehicles."
						);

						break;
						
					case 2: {
						Zombie z(rando_zombie_name() + ", and " + rando_zombie_name(), 10);
						player.inc_st(-10);

						decision_print(
							player.hp,
							"Create a Distraction.",
							"You hurl a glass bottle into a storefront across the street. Most of the horde turns toward the crash, though two stragglers spot you, you take a glancing blow as you sprint past them to the soldiers' barricade."
						);

						break;
					}
					case 3:
						
						Zombie z(rando_zombie_name() + ", " + rando_zombie_name() + ", and " + rando_zombie_name(), 40);
						player.inc_st(-25);

						decision_print(
							player.hp,
							"Force Your Way Through the Crowd.",
							"You lower your shoulder and charge straight into the swarm. Hands grab at your clothes and teeth tear into your arms; only covering gunfire from the rescue perimeter saves you as you collapse across the line."
						);

						break;
				}

				chapter = 12;

				break;

			case 12:
				
				// the final choice

				query_print(
					"October 26, 2026 - 3:00pm",
					choice_formatting(
						"You finally reach the evacuation point. Three vehicles are preparing to leave as infected individuals approach the area. A rescue officer calls for all remaining survivors to board immediately.\n\n You notice three available vehicles. Each has a different person in charge. Which vehicle will you board?",
						"Brent's Vehicle. Rescue Team Member.", "Chiro's Vehicle. Doctor.", "Rainne's Vehicle. Laboratory Scientist."
					)
				);

				if (query_buffer() == 1) {
				
					decision_print(
						player.hp,
						"Brent's Vehicle. Rescue Team Member.",
						"You quickly board Brent's rescue vehicle as the team prepares to leave. The doors close, and the vehicle moves away from the evacuation point just as infected individuals begin approaching.\n\n Through the window, you watch the city disappear into the distance. After three days of surviving the outbreak, making difficult decisions, and fighting to stay alive, you have finally made it.\n\n The rescue team brings you to a secure evacuation center, where medical personnel examine you and confirm that you are not infected.\n\n For the first time since the outbreak began, you can finally breathe without fear.\n\n YOU SURVIVED! YOU HAVE BEEN RESCUED!"
					);

					//input_pause();

					
				} else {

					decision_print(
						player.hp,
						"The Creators.",
						"You board the vehicle, believing that you have finally found a way to escape the outbreak. However, as the journey continues, you overhear Chiro and Rainne discussing something disturbing.\n\n You soon discover the truth: they were the scientists behind the experimental medicine that caused the outbreak. The first laboratory experiment had failed, and the other four participants had become infected. You were the only successful subject, which made you their next priority. \n\n They never intended to rescue you. They planned to take you back to their laboratory and conduct another experiment, hoping to achieve the results they failed to obtain the first time.\n\n Before you can escape, they reveal their true intentions and expose you to the infection once again. You realize that the people you trusted were responsible for everything that happened.\n\n THE EXPERIMENT WAS NEVER OVER. YOU WERE ALWAYS THEIR NEXT TEST SUBJECT."
					);

					//input_pause();

					player.inc_hp(-500);

				}

				chapter = 0;
				active = false;
				retry_code = 1;
				pname = "";
				break;

		}

		// death check
		
		if (player.hp <= 0) {
			print(); separator(25, "! "); print();
			print(choice_formatting(
				"- ~~ !!! YOU DIED !!! ~~ -",
				"RESTART", "MAIN MENU", "QUIT"
			));
			chapter = 0;
			
			switch (query_buffer()) {
				case 1:
					active = false;
					retry_code = 0;
					break;
				case 2:
					active = false;
					retry_code = 1;
					pname = "";
					break;
				case 3:
					active = false;
					retry_code = -1;
					chapter = -2;
					pname = "";
					return;
			}
				
			
		} else {
			if (player.fu <= 0) { // decrement player health if hungry
				player.inc_hp(-10);
			}
		}

	}

	
}

int main() {
	while (true) {
		gameplay();
		if (retry_code == 0) { active = true; gameplay(pname); }
		else if (retry_code == 1) { active = true; gameplay(); }
		else { break; }
	}
	return 0;
}


