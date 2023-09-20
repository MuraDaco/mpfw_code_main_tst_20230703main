//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork 
//      library that contains the "main" entry point and, 
//      eventualy, application code that is platform dependent
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************
/*
 * main.c
 *
 *  Created on: Nov, 22 2022
 *      Author: Marco Dau
 */

// system include
#include <thread>
#include <pthread.h>
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

// module include
#include "main.h"

// lib include
#include <krInitStaticManager.h>
using namespace fw2::core::core;

#include <krThreadManager.h>
using namespace fw2::wrapper::core;

#include <sdk_usart.h>
#include <rsSerial.h>
using namespace fw2::wrapper::resources;

// tst include
#include <tt_MainManager.h>
#include <mn/tt_mn_svSyncMain.h>

// tst/tb include
#include <app/krThreadTbl.h>
#include <app/krTimerTbl.h>
#include <app/svStateMachineTbl.h>
using namespace mpfw::apps;

void thread_service_rsSerial() {

	while(1){if(!sdk_usart::loop()) break;}

}

int main()
{
    std::thread thread_service;

    rsSerial::Init();
	sdk_usart::start();

    thread_service = std::thread(thread_service_rsSerial);

    // ***************************************************************************
    krInitStaticManager::LoopOnUnits();     
    rsSerial::Tx(rsSerial::endl);

    // ***************************************************************************
    rsSerial::Tx("START  - Main"); rsSerial::Tx(rsSerial::endl);

    // ***************************************************************************
    rsSerial::Tx("START  - Setup Timer Service"); rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);

    // ***************************************************************************
    rsSerial::Tx("START  - Setup State Machine Service"); rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);

    // ***************************************************************************
    rsSerial::Tx("START  - Threads definition and then run them"); rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);
    krThreadManager::InitThenRun();
    
    // do {
    //     sleep_for(10ms);
    // } while (tt_mn_svSyncMain::CheckRaceConditionCounter(10));
    

    // ***************************************************************************
    krThreadManager::Exit();
    rsSerial::Tx("EXIT  - from Main Loop"); rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);
    rsSerial::Tx(rsSerial::endl);

    //// ***************************************************************************
    //rsSerial::Tx("SHOW  - Tests results"); rsSerial::Tx(rsSerial::endl);
    //rsSerial::Tx(rsSerial::endl);
    //tt_MainManager::LoopOnUnits();
    //rsSerial::Tx(rsSerial::endl);


    thread_service.join();

	sdk_usart::end();

}

