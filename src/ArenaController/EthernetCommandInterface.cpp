//.$file${./ArenaControlle~::EthernetCommandInterface.cpp} vvvvvvvvvvvvvvvvvvv
//
// Model: ArenaController.qm
// File:  ${./ArenaControlle~::EthernetCommandInterface.cpp}
//
// This code has been generated by QM 5.1.3 <www.state-machine.com/qm/>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
//.$endhead${./ArenaControlle~::EthernetCommandInterface.cpp} ^^^^^^^^^^^^^^^^
#include "EthernetCommandInterface.hpp"


using namespace QP;

//============================================================================
// generate definition of to opaque pointer to the AO
//.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//. Check for the minimum required QP version
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.9.0 or higher required
#endif
//.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//.$define${Shared::AO_EthernetCommandInterface} vvvvvvvvvvvvvvvvvvvvvvvvvvvvv
namespace AC {

//.${Shared::AO_EthernetCommandInterface} ....................................
QP::QActive * const AO_EthernetCommandInterface = &EthernetCommandInterface::instance;

} // namespace AC
//.$enddef${Shared::AO_EthernetCommandInterface} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//============================================================================
// generate definition of the AO
//.$define${AOs::EthernetCommandInterface} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
namespace AC {

//.${AOs::EthernetCommandInterface} ..........................................
EthernetCommandInterface EthernetCommandInterface::instance;
//.${AOs::EthernetCommandI~::EthernetCommandInterface} .......................
EthernetCommandInterface::EthernetCommandInterface()
: QActive(Q_STATE_CAST(&EthernetCommandInterface::initial)),
    ethernet_time_evt_(this, ETHERNET_TIMEOUT_SIG, 0U)
{}

//.${AOs::EthernetCommandI~::SM} .............................................
Q_STATE_DEF(EthernetCommandInterface, initial) {
    //.${AOs::EthernetCommandI~::SM::initial}
    subscribe(SERIAL_COMMAND_AVAILABLE_SIG);
    subscribe(ETHERNET_COMMAND_AVAILABLE_SIG);
    subscribe(COMMAND_PROCESSED_SIG);
    return tran(&Inactive);
}
//.${AOs::EthernetCommandI~::SM::Inactive} ...................................
Q_STATE_DEF(EthernetCommandInterface, Inactive) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Inactive::ACTIVATE_ETHERNET_COMMAND_INTERF~}
        case ACTIVATE_ETHERNET_COMMAND_INTERFACE_SIG: {
            status_ = tran(&Active);
            break;
        }
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active} .....................................
Q_STATE_DEF(EthernetCommandInterface, Active) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active}
        case Q_ENTRY_SIG: {
            ethernet_time_evt_.armX(BSP::TICKS_PER_SEC/2, BSP::TICKS_PER_SEC/50);
            status_ = Q_RET_HANDLED;
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active}
        case Q_EXIT_SIG: {
            ethernet_time_evt_.disarm();
            status_ = Q_RET_HANDLED;
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::initial}
        case Q_INIT_SIG: {
            status_ = tran(&Unintitalized);
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::DEACTIVATE_ETHERNET_COMMAND_INTE~}
        case DEACTIVATE_ETHERNET_COMMAND_INTERFACE_SIG: {
            status_ = tran(&Inactive);
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::ETHERNET_TIMEOUT}
        case ETHERNET_TIMEOUT_SIG: {
            status_ = Q_RET_HANDLED;
            break;
        }
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::Unintitalized} ......................
Q_STATE_DEF(EthernetCommandInterface, Unintitalized) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::Unintitalized::ETHERNET_INITIALIZED}
        case ETHERNET_INITIALIZED_SIG: {
            status_ = tran(&WaitingForIPAddress);
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::Unintitalized::ETHERNET_TIMEOUT}
        case ETHERNET_TIMEOUT_SIG: {
            BSP::beginEthernet();
            status_ = Q_RET_HANDLED;
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::IPAddressFound} .....................
Q_STATE_DEF(EthernetCommandInterface, IPAddressFound) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::IPAddressFound::ETHERNET_SERVER_INITIALIZED}
        case ETHERNET_SERVER_INITIALIZED_SIG: {
            status_ = tran(&PollingForNewCommand);
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::IPAddressFound::ETHERNET_TIMEOUT}
        case ETHERNET_TIMEOUT_SIG: {
            BSP::beginEthernetServer();
            status_ = Q_RET_HANDLED;
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::PollingForNewCommand} ...............
Q_STATE_DEF(EthernetCommandInterface, PollingForNewCommand) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::PollingForNewCom~::ETHERNET_TIMEOUT}
        case ETHERNET_TIMEOUT_SIG: {
            BSP::pollEthernetCommand();
            status_ = Q_RET_HANDLED;
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::PollingForNewCom~::SERIAL_COMMAND_AVAILABLE}
        case SERIAL_COMMAND_AVAILABLE_SIG: {
            status_ = tran(&Waiting);
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::PollingForNewCom~::ETHERNET_COMMAND_AVAILABLE}
        case ETHERNET_COMMAND_AVAILABLE_SIG: {
            status_ = tran(&ProcessingCommand);
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::WaitingForIPAddress} ................
Q_STATE_DEF(EthernetCommandInterface, WaitingForIPAddress) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::WaitingForIPAddr~::ETHERNET_TIMEOUT}
        case ETHERNET_TIMEOUT_SIG: {
            BSP::checkForEthernetIPAddress();
            status_ = Q_RET_HANDLED;
            break;
        }
        //.${AOs::EthernetCommandI~::SM::Active::WaitingForIPAddr~::ETHERNET_IP_ADDRESS_FOUND}
        case ETHERNET_IP_ADDRESS_FOUND_SIG: {
            status_ = tran(&IPAddressFound);
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::Waiting} ............................
Q_STATE_DEF(EthernetCommandInterface, Waiting) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::Waiting::COMMAND_PROCESSED}
        case COMMAND_PROCESSED_SIG: {
            status_ = tran(&PollingForNewCommand);
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}
//.${AOs::EthernetCommandI~::SM::Active::ProcessingCommand} ..................
Q_STATE_DEF(EthernetCommandInterface, ProcessingCommand) {
    QP::QState status_;
    switch (e->sig) {
        //.${AOs::EthernetCommandI~::SM::Active::ProcessingComman~::COMMAND_PROCESSED}
        case COMMAND_PROCESSED_SIG: {
            status_ = tran(&PollingForNewCommand);
            break;
        }
        default: {
            status_ = super(&Active);
            break;
        }
    }
    return status_;
}

} // namespace AC
//.$enddef${AOs::EthernetCommandInterface} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
