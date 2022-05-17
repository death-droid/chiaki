#ifndef RPI_HOST_H
#define RPI_HOST_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <chiaki/controller.h>
#include <chiaki/log.h>
#include <chiaki/opusdecoder.h>
#include <chiaki/regist.h>
#include <chiaki/session.h>

#include <chiaki/discovery.h>
#include <chiaki/discoveryservice.h>

#include <rpi/io.h>
#include <rpi/gui.h>

#define HOSTS_MAX	4		// was 16

//typedef void (*ChiakiDiscoveryServiceCb)(ChiakiDiscoveryHost *hosts, size_t hosts_count, void *user);
//~ static void Discovery(ChiakiDiscoveryHost *, void *);
//~ static void EventCB(ChiakiEvent *event, void *user);
//~ static void DiscoveryCB(void *user);//not used?

// Rename this Class Hosts?

class Host
{
	private:
		ChiakiConnectVideoProfile video_profile;
		ChiakiAudioSink audio_sink;
		
		/// REGISTERING
		ChiakiRegistInfo regist_info = {};
		ChiakiRegist regist;
		size_t accId_len;
		
	public:
		ChiakiLog log;
		IO *io = nullptr; ///should be private
		ImguiSdlWindow *gui = nullptr;
		ChiakiConnectInfo connect_info;
		bool session_init = false;
		ChiakiSession session;
		ChiakiOpusDecoder opus_decoder;
		ChiakiTarget target = CHIAKI_TARGET_PS4_UNKNOWN;
		std::string state = "";  /// standby, unknown, ready etc
		ChiakiDiscoveryService *service;
		ChiakiDiscoveryHost *discoveredHosts = nullptr;
		bool ps5 = false;	// MUST REMOVE set by Discovery, not config read (overwrite if Config exists?)
		rpi_settings_host session_settings;
		
		/// Remotes
		rpi_settings_host current_remote_settings;
		rpi_settings_host discovered_remote;
		std::string remote_state = "";  /// standby, unknown, ready etc
		bool discoveredRemoteMatched = false;
		unsigned int testCount=0; // should be in Gui no?

		ChiakiThread play_th;
		
		Host();
		~Host();
		int Init(IO *io);
		int StartDiscoveryService();
		int DiscoverRemote();
		int WakeupRemote();
		void RegistStart(std::string accountID, std::string pin);
		void SendWakeup();
		int StartSession();
		void Play();
		std::string GetHostRPKey(uint8_t rp_key[]);
		
		//void DiscoveryCB(ChiakiDiscoveryHost *discovered_host);
		void ConnectionEventCB(ChiakiEvent *event);

};
#endif
