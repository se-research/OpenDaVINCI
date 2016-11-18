/************************************************************************/
/*                                                                      */
/* This file is part of VDrift.                                         */
/*                                                                      */
/* VDrift is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* VDrift is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with VDrift.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                      */
/************************************************************************/

#ifndef _GAME_H
#define _GAME_H

#include "window.h"
#include "graphics/graphics.h"
#include "graphics/gl3v/stringidmap.h"
#include "eventsystem.h"
#include "settings.h"
#include "pathmanager.h"
#include "track.h"
#include "mathvector.h"
#include "quaternion.h"
#include "http.h"
#include "gui/gui.h"
#include "gui/text_draw.h"
#include "gui/font.h"
#include "physics/dynamicsworld.h"
#include "physics/cardynamics.h"
#include "dynamicsdraw.h"
#include "carcontrolmap.h"
#include "cargraphics.h"
#include "carsound.h"
#include "carinfo.h"
#include "sound/sound.h"
#include "camera.h"
#include "camera_free.h"
#include "trackmap.h"
#include "timer.h"
#include "replay.h"
#include "forcefeedback.h"
#include "particle.h"
#include "ai/ai.h"
#include "content/contentmanager.h"
#include "updatemanager.h"
#include "game_downloader.h"

#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"
#include "controller-lib/PIDController.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iosfwd>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <memory>


class Game : public odcore::base::module::TimeTriggeredConferenceClientModule
{
friend class GameDownloader;
public:
	Game(int argc, char **argv, std::ostream & info_out, std::ostream & error_out);

	~Game();

	void Start(std::list <std::string> & args);

private:
    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();
    virtual void setUp();
    virtual void tearDown();
	std::vector <float> inputFromOpenDaVINCI;

	int angle(int x1, int y1, int x2, int y2) {
		std::cout << "ANGLE(): slope" << std::endl;
		if (x1 == x2) return -1;

		int val = (y2-y1)/(x2-x1); // calculate slope between the two points
		std::cout << "ANGLE(): arctan" << std::endl;
		val = val - pow(val,3)/3 + pow(val,5)/5; // find arc tan of the slope using taylor series approximation
		std::cout << "ANGLE(): radians" << std::endl;
		val = ((int)(val*180/3.14)) % 360; // Convert the angle in radians to degrees
		std::cout << "ANGLE(): normalize" << std::endl;
		if (x2 < x1) val+=180;
		if (val < 0) val = 360 + val;
		return val;
	}

	void renderText(const std::string& text, int y) {
		cv::putText(imageHeader_, text, cv::Point(30,y),cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,0), 1, CV_AA);
	}

    void attachToSharedMemory(const odcore::data::image::SharedImage & sharedImage);
	void End();

	void MainLoop();

	bool ParseArguments(std::list <std::string> & args);

	bool InitCoreSubsystems();

	void InitThreading();

	void InitPlayerCar();

	bool InitSound();

	bool InitGUI();

	void Test();

	void Tick(float dt);

	void TickOpenDaVINCI(float dt);

	void Draw();

	void AdvanceGameLogic();

	void UpdateCars(float dt);

	void ProcessCarInputs(const size_t carid);

	/// Updates camera, call after physics update
	void ProcessCameraInputs();

	void UpdateHUD(const size_t carid, const std::vector<float> & carinputs);

	void UpdateTimer();

	/// Check eventsystem state and update GUI
	void ProcessGUIInputs();

	void ProcessGameInputs();

	void UpdateStartList();

	void UpdateCarPosList();

	void UpdateCarInfo();

	bool NewGame(bool playreplay=false, bool opponents=false, int num_laps=0);

	bool LoadCar(
		const CarInfo & carinfo,
		const Vec3 & position,
		const Quat & orientation,
		const bool sound_enabled);

	bool LoadTrack(const std::string & trackname);

	void LoadGarage();

	void SetGarageCar();

	void SetCarColor();

	bool LoadFonts();

	void CalculateFPS();

	void PopulateValueLists(std::map<std::string, GuiOption::List> & valuelists);

	void PopulateTrackList(GuiOption::List & tracklist);

	void PopulateCarList(GuiOption::List & carlist, bool cardironly = false);

	void PopulateCarPaintList(const std::string & carname, GuiOption::List & paintlist);

	void PopulateCarTireList(const std::string & carname, GuiOption::List & tirelist);

	void PopulateCarWheelList(const std::string & carname, GuiOption::List & wheellist);

	void PopulateDriverList(GuiOption::List & driverlist);

	void PopulateStartList(GuiOption::List & startlist);

	void PopulateReplayList(GuiOption::List & replaylist);

	void PopulateGUISkinList(GuiOption::List & skinlist);

	void PopulateGUILangList(GuiOption::List & langlist);

	void PopulateAnisoList(GuiOption::List & anisolist);

	void PopulateAntialiasList(GuiOption::List & antialiaslist);

	void UpdateTrackMap();

	void ShowLoadingScreen(float progress, float progress_max, const std::string & optional_text);

	void ProcessNewSettings();

	/// Look for keyboard, mouse, joystick input, assign local car controls.
	bool AssignControl();

	void LoadControlsIntoGUIPage(const std::string & page_name);

	void LoadControlsIntoGUI();

	void UpdateForceFeedback(float dt);

	void AddTireSmokeParticles(const CarDynamics & car, float dt);

	void UpdateParticles(float dt);

	void UpdateParticleGraphics();

	void UpdateDriftScore(const int carid, const float dt);

	std::string GetReplayRecordingFilename();

	void Draw(float dt);

	void BeginStartingUp();

	void DoneStartingUp();

	bool LastStartWasSuccessful() const;

	bool Download(const std::string & file);

	bool Download(const std::vector <std::string> & files);

	// game actions
	void QuitGame();
	void LeaveGame();
	void StartRace();
	void PauseGame();
	void ContinueGame();
	void RestartGame();
	void StartReplay();
	void HandleOnlineClicked();
	void StartCheckForUpdates();
	void StartCarManager();
	void CarManagerNext();
	void CarManagerPrev();
	void ApplyCarUpdate();
	void StartTrackManager();
	void TrackManagerNext();
	void TrackManagerPrev();
	void ApplyTrackUpdate();
	void ActivateEditControlPage();
	void CancelControl();
	void DeleteControl();
	void SetButtonControl();
	void SetAnalogControl();
	void LoadControls();
	void SaveControls();
	void SyncOptions();
	void SyncSettings();
	void SelectPlayerCar();

	void SetCarToEdit(const std::string & value);
	void SetCarStartPos(const std::string & value);
	void SetCarName(const std::string & value);
	void SetCarPaint(const std::string & value);
	void SetCarTire(const std::string & value);
	void SetCarWheel(const std::string & value);
	void SetCarColor(const std::string & value);
	void SetCarColorHue(const std::string & value);
	void SetCarColorSat(const std::string & value);
	void SetCarColorVal(const std::string & value);
	void SetCarDriver(const std::string & value);
	void SetCarAILevel(const std::string & value);
	void SetCarsNum(const std::string & value);
	void SetControl(const std::string & value);


	void BindActionsToGUI();
	void RegisterActions();
	void InitActionMap(std::map<std::string, Slot0*> & actionmap);
	void InitSignalMap(std::map<std::string, Signal1<const std::string &>*> & signalmap);

	void writeResults(const std::string filename);

	Slot1<const std::string &> set_car_toedit;
	Slot1<const std::string &> set_car_startpos;
	Slot1<const std::string &> set_car_name;
	Slot1<const std::string &> set_car_paint;
	Slot1<const std::string &> set_car_tire;
	Slot1<const std::string &> set_car_wheel;
	Slot1<const std::string &> set_car_color_hue;
	Slot1<const std::string &> set_car_color_sat;
	Slot1<const std::string &> set_car_color_val;
	Slot1<const std::string &> set_car_driver;
	Slot1<const std::string &> set_car_ailevel;
	Slot1<const std::string &> set_cars_num;
	Slot1<const std::string &> set_control;
	std::vector<Slot0> actions;

	// game info signals
	Signal1<const std::string &> signal_loading;
	Signal1<const std::string &> signal_fps;

	// hud info signals
	Signal1<const std::string &> signal_debug_info[4];
	Signal1<const std::string &> signal_message;
	Signal1<const std::string &> signal_lap_time[3];
	Signal1<const std::string &> signal_lap;
	Signal1<const std::string &> signal_pos;
	Signal1<const std::string &> signal_score;
	Signal1<const std::string &> signal_steering;
	Signal1<const std::string &> signal_throttle;
	Signal1<const std::string &> signal_brake;
	Signal1<const std::string &> signal_gear;
	Signal1<const std::string &> signal_shift;
	Signal1<const std::string &> signal_speedometer;
	Signal1<const std::string &> signal_speed_norm;
	Signal1<const std::string &> signal_speed;
	Signal1<const std::string &> signal_tachometer;
	Signal1<const std::string &> signal_rpm_norm;
	Signal1<const std::string &> signal_rpm_red;
	Signal1<const std::string &> signal_rpm;
	Signal1<const std::string &> signal_abs;
	Signal1<const std::string &> signal_tcs;
	Signal1<const std::string &> signal_gas;
	Signal1<const std::string &> signal_nos;

	std::ostream & info_output;
	std::ostream & error_output;

	unsigned int frame; ///< physics frame counter
	unsigned int displayframe; ///< display frame counter
	double clocktime; ///< elapsed wall clock time
	double target_time;
	const float timestep; ///< simulation time step

	PathManager pathmanager;
	Settings settings;
	Window window;
	Graphics * graphics;
	StringIdMap stringMap;
	EventSystem eventsystem;
	ContentManager content;
	Sound sound;
	AutoUpdate autoupdate;
	UpdateManager carupdater;
	UpdateManager trackupdater;
	std::map <std::string, Font> fonts;
	std::string renderconfigfile;

	std::vector <float> fps_track;
	int fps_position;
	float fps_min;
	float fps_max;

	bool multithreaded;
	bool profilingmode;
	bool benchmode;
	bool dumpfps;
	bool pause;

	std::vector <EventSystem::Joystick> controlgrab_joystick_state;
	std::pair <int,int> controlgrab_mouse_coords;
	CarControlMap::Control controlgrab_control;
	std::string controlgrab_page;
	std::string controlgrab_input;
	size_t controlgrab_id;
	bool controlgrab;

	CameraFree garage_camera;
	Camera * active_camera;

	std::pair <CarDynamics *, CarControlMap> carcontrols_local;
	btAlignedObjectArray <CarDynamics> car_dynamics;
	std::vector <CarGraphics> car_graphics;
	std::vector <CarSound> car_sounds;
	std::vector <CarInfo> car_info;
	size_t player_car_id;
	size_t car_edit_id;
	int race_laps;
	bool practice;

	btDefaultCollisionConfiguration collisionconfig;
	btCollisionDispatcher collisiondispatch;
	btDbvtBroadphase collisionbroadphase;
	btSequentialImpulseConstraintSolver collisionsolver;
	DynamicsDraw dynamicsdraw;
	DynamicsWorld dynamics;
	int dynamics_drawmode;

	ParticleSystem tire_smoke;
	unsigned int particle_timer;

	TrackMap trackmap;
	Track track;
	Gui gui;
	Timer timer;
	Replay replay;
	Ai ai;
	Http http;

	std::unique_ptr <ForceFeedback> forcefeedback;
	double ff_update_time;
	
	
    std::shared_ptr<odcore::wrapper::SharedMemory> sharedImageMemory_;
    cv::Mat imageHeader_, testImage, testImage2;

    std::ostringstream stringStream;
    time_t m_lastScreenshot;
    const int ROW_COUNT = 3;
    int m_line = 0;
    std::vector<std::string> vanishingPoints; // frameID, x, y
    int frameCounter;

    bool extractMode = false;
    std::string workingDirectory = "";
    std::string trackName = "";
    bool automatedDriver = false;

    PIDController gammaPID;
    PIDController speedPID;
    double normed;
    double gamma;

};

#endif
