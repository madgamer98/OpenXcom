/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "NewGameModeState.h"
#include "NewGameState.h"
#include "../Engine/Game.h"
#include "../Mod/Mod.h"
#include "../Interface/TextButton.h"
#include "../Interface/ToggleTextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Geoscape/GeoscapeState.h"
#include "../Geoscape/BuildNewBaseState.h"
#include "../Geoscape/BaseNameState.h"
#include "../Basescape/PlaceLiftState.h"
#include "../Engine/Options.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/Base.h"

namespace OpenXcom
{

/**
* Initializes all the elements in the Multiplayer window.
* @param game Pointer to the core game.
*/
NewGameModeState::NewGameModeState()
{
	// Create objects
	_window = new Window(this, 192, 180, 64, 10, POPUP_VERTICAL);
	_btnSolo = new TextButton(160, 18, 80, 32);
	_btnHost = new TextButton(160, 18, 80, 52);
	_btnClient = new TextButton(160, 18, 80, 72);
	_btnOk = new TextButton(78, 16, 80, 164);
	_btnCancel = new TextButton(78, 16, 162, 164);
	_txtTitle = new Text(192, 9, 64, 20);

	// Set palette
	setInterface("newGameMenu");

	add(_window, "window", "newGameMenu");
	add(_btnSolo, "button", "newGameMenu");
	add(_btnHost, "button", "newGameMenu");
	add(_btnClient, "button", "newGameMenu");
	add(_btnOk, "button", "newGameMenu");
	add(_btnCancel, "button", "newGameMenu");
	add(_txtTitle, "text", "newGameMenu");

	centerAllSurfaces();

	// Set up objects
	setWindowBackground(_window, "newGameMenu");

	_btnSolo->setText(tr("STR_SOLO"));
	_btnSolo->setGroup(&_btnSolo);

	_btnHost->setText(tr("STR_HOST"));
	_btnHost->setGroup(&_btnSolo);

	_btnClient->setText(tr("STR_CLIENT"));
	_btnClient->setGroup(&_btnSolo);

	_btnOk->setText(tr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&NewGameModeState::btnOkClick);
	_btnOk->onKeyboardPress((ActionHandler)&NewGameModeState::btnOkClick, Options::keyOk);

	_btnCancel->setText(tr("STR_CANCEL"));
	_btnCancel->onMouseClick((ActionHandler)&NewGameModeState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&NewGameModeState::btnCancelClick, Options::keyCancel);

	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(tr("STR_GAMEMODE"));
}

/**
*
*/
NewGameModeState::~NewGameModeState()
{

}

/**
* Returns to the previous screen.
* @param action Pointer to an action.
*/
void NewGameModeState::btnOkClick(Action*)
{
	// Reset touch flags
	_game->resetTouchButtonFlags();

	SavedGame* save = _game->getMod()->newSave(DIFF_BEGINNER);
	//save->setDifficulty(diff);
	//save->setIronman(_btnIronman->getPressed());
	_game->setSavedGame(save);

	_game->pushState(new NewGameState);
}

/**
* Returns to the previous screen.
* @param action Pointer to an action.
*/
void NewGameModeState::btnCancelClick(Action*)
{
	_game->setSavedGame(0);
	_game->popState();
}

}
