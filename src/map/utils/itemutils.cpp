﻿/*
===========================================================================

  Copyright (c) 2010-2014 Darkstar Dev Teams

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/

  This file is part of DarkStar-server source code.

===========================================================================
*/

#include <string.h>

#include "../entities/battleentity.h"
#include "../map.h"
#include "itemutils.h"

CItem *		g_pItemList[MAX_ITEMID];    // глобальный массив указателей на игровые предметы
DropList_t* g_pDropList[MAX_DROPID];    // глобальный массив списков выпадающих предметов
LootList_t* g_pLootList[MAX_LOOTID];

CItemWeapon* PUnarmedItem;
CItemWeapon* PUnarmedH2HItem;

/************************************************************************
*                                                                       *
*  Собственно методы работы с глобальной коллекцией предметов           *
*                                                                       *
************************************************************************/

namespace itemutils
{

    /************************************************************************
    *                                                                       *
    *  Создаем пустой экземпляр предмета по ID (private метод)              *
    *                                                                       *
    ************************************************************************/

    CItem* CreateItem(uint16 ItemID) 
    {
	    if( (ItemID >= 0x0200) && (ItemID <= 0x0206) ) 
	    {
		    return new CItemLinkshell(ItemID);
	    }
	    if( (ItemID >= 0x01D8) && (ItemID <= 0x0DFF) ) 
	    {
		    return new CItemGeneral(ItemID);
	    }
	    if( (ItemID >= 0x0000) && (ItemID <= 0x0FFF) ) 
	    {
		    return new CItemFurnishing(ItemID);
	    }
	    if( (ItemID >= 0x1000) && (ItemID <= 0x17FF) ) 
	    {
		    return new CItemUsable(ItemID);
	    }
	    if( (ItemID >= 0x2000) && (ItemID <= 0x27FF) ) 
	    {
		    return new CItemPuppet(ItemID);
	    }
	    if( (ItemID >= 0x2800) && (ItemID <= 0x3FFF) ) 
	    {
		    return new CItemArmor(ItemID);
	    }
	    if( (ItemID >= 0x4000) && (ItemID <= 0x5FFF) ) 
	    {
		    return new CItemWeapon(ItemID);
	    }
		if( (ItemID >= 0x6000) && (ItemID <= 0x6FFF) )
		{
			return new CItemArmor(ItemID);
		}
		if( (ItemID >= 0x7000) && (ItemID <= 0x7FFF) )
		{
			return new CItemGeneral(ItemID);
		}


	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *  Создаем новый экземпляр предмета по ID                               *
    *                                                                       *
    ************************************************************************/

    CItem* GetItem(uint16 ItemID)
    {
	    if( (ItemID == 0xFFFF) ) 
	    {
		    return new CItemCurrency(ItemID);
	    }
	    if (ItemID < MAX_ITEMID && g_pItemList[ItemID] != NULL)
	    {
		    if( (ItemID >= 0x0200) && (ItemID <= 0x0206) ) 
		    {
			    return new CItemLinkshell(*((CItemLinkshell*)g_pItemList[ItemID]));
		    }
		    if( (ItemID >= 0x01D8) && (ItemID <= 0x0DFF) ) 
		    {
			    return new CItemGeneral(*((CItemGeneral*)g_pItemList[ItemID]));
		    }
		    if( (ItemID >= 0x0000) && (ItemID <= 0x0FFF) ) 
		    {
			    return new CItemFurnishing(*((CItemFurnishing*)g_pItemList[ItemID]));
		    }
		    if( (ItemID >= 0x1000) && (ItemID <= 0x17FF) ) 
		    {
			    return new CItemUsable(*((CItemUsable*)g_pItemList[ItemID]));
		    }
		    if( (ItemID >= 0x2000) && (ItemID <= 0x27FF) ) 
		    {
			    return new CItemPuppet(*((CItemPuppet*)g_pItemList[ItemID]));
		    }
		    if( ((ItemID >= 0x2800) && (ItemID <= 0x3FFF))) 
		    {
			    return new CItemArmor(*((CItemArmor*)g_pItemList[ItemID]));
		    }
		    if( (ItemID >= 0x4000) && (ItemID <= 0x5FFF) )
		    {
			    return new CItemWeapon(*((CItemWeapon*)g_pItemList[ItemID]));
		    }
			if( (ItemID >= 0x6000) && (ItemID <= 0x6FFF) )
			{
				return new CItemArmor(*((CItemArmor*)g_pItemList[ItemID]));
			}
			if( (ItemID >= 0x7000) && (ItemID <= 0x7FFF) )
			{
			    return new CItemGeneral(*((CItemGeneral*)g_pItemList[ItemID]));
			}
	    }
	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *  Создаем копию предмета                                               *
    *                                                                       *
    ************************************************************************/

    CItem* GetItem(CItem* PItem)
    {
        DSP_DEBUG_BREAK_IF(PItem == NULL);

        if (PItem->isType(ITEM_WEAPON))
        {
            return new CItemWeapon(*((CItemWeapon*)PItem));
        }
        if (PItem->isType(ITEM_ARMOR))
        {
            return new CItemArmor(*((CItemArmor*)PItem));
        }
        if (PItem->isType(ITEM_USABLE))
        {
            return new CItemUsable(*((CItemUsable*)PItem));
        }
        if (PItem->isType(ITEM_LINKSHELL))
        {
            return new CItemLinkshell(*((CItemLinkshell*)PItem));
        }
        if (PItem->isType(ITEM_FURNISHING))
        {
            return new CItemFurnishing(*((CItemFurnishing*)PItem));
        }
        if (PItem->isType(ITEM_PUPPET))
        {
            return new CItemPuppet(*((CItemPuppet*)PItem));
        }
        if (PItem->isType(ITEM_GENERAL))
        {
            return new CItemGeneral(*((CItemGeneral*)PItem));
        }
	    if (PItem->isType(ITEM_CURRENCY))
        {
            return new CItemCurrency(*((CItemCurrency*)PItem));
        }
        return NULL;
    }

    /************************************************************************
    *                                                                       *
    *  Получаем указатель на предмет из коллекции (только для чтения)       *
    *                                                                       *
    ************************************************************************/

    CItem* GetItemPointer(uint16 ItemID)
    {
	    if (ItemID < MAX_ITEMID)
	    {
		    return g_pItemList[ItemID];
	    }
        ShowWarning(CL_CYAN"ItemID %u too big\n" CL_RESET, ItemID);
	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *                                                                       *
    *                                                                       *
    ************************************************************************/

    CItemWeapon* GetUnarmedItem()
    {
        return PUnarmedItem;
    }

    CItemWeapon* GetUnarmedH2HItem()
    {
        return PUnarmedH2HItem;
    }

    /************************************************************************
    *                                                                       *
    *  Список выпадаемых из монстров предметов                              *
    *                                                                       *
    ************************************************************************/

    DropList_t* GetDropList(uint16 DropID)
    {
	    if (DropID < MAX_DROPID)
	    {
		     return g_pDropList[DropID];
	    }
        ShowWarning(CL_CYAN"DropID %u too big\n" CL_RESET, DropID);
	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *                                                                       *
    *                                                                       *
    ************************************************************************/

    LootList_t* GetLootList(uint16 LootID)
    {
	    if (LootID < MAX_LOOTID)
	    {
		     return g_pLootList[LootID];
	    }
        ShowWarning(CL_CYAN"LootID %u too big\n" CL_RESET, LootID);
	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *  Загружаем базу предметов                                             *
    *                                                                       *
    ************************************************************************/

    void LoadItemList()
    {
	    memset(g_pItemList,0,sizeof(g_pItemList));
	    memset(g_pDropList,0,sizeof(g_pDropList));

	    const int8* Query =    
            "SELECT "
                "b.itemId,"         //  0
                "b.name,"           //  1
                "b.stackSize,"      //  2
                "b.flags,"          //  3
                "b.aH,"             //  4
                "b.BaseSell,"       //  5
			    "b.subid,"          //  6

                "u.validTargets,"   //  7
                "u.activation,"     //  8
                "u.animation,"      //  9
                "u.animationTime,"  // 10
                "u.maxCharges,"     // 11
                "u.useDelay,"       // 12
                "u.reuseDelay,"     // 13
                "u.aoe,"            // 14
								       
                "a.level,"          // 15
                "a.jobs,"           // 16
                "a.MId,"            // 17
                "a.shieldSize,"     // 18
                "a.scriptType,"     // 19
                "a.slot,"           // 20
                "a.rslot,"          // 21

			    "w.skill,"          // 22
				"w.subskill,"       // 23
                "w.delay,"          // 24
                "w.dmg,"            // 25
                "w.dmgType,"        // 26
                "w.hit,"            // 27
                "w.unlock_index,"   // 28
								       
                "f.storage,"        // 29
                "f.moghancement,"   // 30
                "f.element,"        // 31
                "f.aura,"           // 32

                "p.slot,"           // 33
                "p.element "        // 34
		    "FROM item_basic AS b "
		    "LEFT JOIN item_usable AS u USING (itemId) "
		    "LEFT JOIN item_armor  AS a USING (itemId) "
		    "LEFT JOIN item_weapon AS w USING (itemId) "
		    "LEFT JOIN item_furnishing AS f USING (itemId) "
            "LEFT JOIN item_puppet AS p USING (itemId) "
		    "WHERE itemId < %u;";

	    int32 ret = Sql_Query(SqlHandle, Query, MAX_ITEMID);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
		    {
			    CItem* PItem = CreateItem(Sql_GetUIntData(SqlHandle,0));

			    if(PItem != NULL)
			    {
				    PItem->setName(Sql_GetData(SqlHandle,1));
				    PItem->setStackSize(Sql_GetUIntData(SqlHandle,2));
				    PItem->setFlag(Sql_GetUIntData(SqlHandle,3));
				    PItem->setAHCat(Sql_GetUIntData(SqlHandle,4));
				    PItem->setBasePrice(Sql_GetUIntData(SqlHandle,5));
					PItem->setSubID(Sql_GetUIntData(SqlHandle,6));
				
				    if (PItem->isType(ITEM_GENERAL))
				    {

				    }
				    if (PItem->isType(ITEM_USABLE))
				    {
					    ((CItemUsable*)PItem)->setValidTarget(Sql_GetUIntData(SqlHandle,7));
					    ((CItemUsable*)PItem)->setActivationTime(Sql_GetUIntData(SqlHandle,8)*1000);
					    ((CItemUsable*)PItem)->setAnimationID(Sql_GetUIntData(SqlHandle,9));
					    ((CItemUsable*)PItem)->setAnimationTime(Sql_GetUIntData(SqlHandle,10)*1000);
					    ((CItemUsable*)PItem)->setMaxCharges(Sql_GetUIntData(SqlHandle,11));
					    ((CItemUsable*)PItem)->setCurrentCharges(Sql_GetUIntData(SqlHandle,11));
					    ((CItemUsable*)PItem)->setUseDelay(Sql_GetUIntData(SqlHandle,12));
					    ((CItemUsable*)PItem)->setReuseDelay(Sql_GetUIntData(SqlHandle,13));
                        ((CItemUsable*)PItem)->setAoE(Sql_GetUIntData(SqlHandle,14));
				    }
				    if (PItem->isType(ITEM_PUPPET))
				    {
                        ((CItemPuppet*)PItem)->setEquipSlot(Sql_GetUIntData(SqlHandle,33));
                        ((CItemPuppet*)PItem)->setElementSlots(Sql_GetUIntData(SqlHandle,34));
				    }
				    if (PItem->isType(ITEM_ARMOR))
				    {
					    ((CItemArmor*)PItem)->setReqLvl(Sql_GetUIntData(SqlHandle,15));
					    ((CItemArmor*)PItem)->setJobs(Sql_GetUIntData(SqlHandle,16));
					    ((CItemArmor*)PItem)->setModelId(Sql_GetUIntData(SqlHandle,17));
					    ((CItemArmor*)PItem)->setShieldSize(Sql_GetUIntData(SqlHandle,18));
					    ((CItemArmor*)PItem)->setScriptType(Sql_GetUIntData(SqlHandle,19));
					    ((CItemArmor*)PItem)->setEquipSlotId(Sql_GetUIntData(SqlHandle,20));
					    ((CItemArmor*)PItem)->setRemoveSlotId(Sql_GetUIntData(SqlHandle,21));

					    if (((CItemArmor*)PItem)->getValidTarget() != 0)
					    {
						    ((CItemArmor*)PItem)->setSubType(ITEM_CHARGED);
					    }
				    }
				    if (PItem->isType(ITEM_WEAPON))
				    {
						((CItemWeapon*)PItem)->setSkillType(Sql_GetUIntData(SqlHandle,22));
						((CItemWeapon*)PItem)->setSubSkillType(Sql_GetUIntData(SqlHandle,23));
					    ((CItemWeapon*)PItem)->setDelay((Sql_GetIntData(SqlHandle,24)*1000)/60);
					    ((CItemWeapon*)PItem)->setDamage(Sql_GetUIntData(SqlHandle,25));
					    ((CItemWeapon*)PItem)->setDmgType(Sql_GetUIntData(SqlHandle,26));
                        ((CItemWeapon*)PItem)->setMaxHit(Sql_GetUIntData(SqlHandle,27));
                        ((CItemWeapon*)PItem)->setUnlockable(Sql_GetUIntData(SqlHandle,28));
				    }
				    if (PItem->isType(ITEM_FURNISHING))
				    {
					    ((CItemFurnishing*)PItem)->setStorage(Sql_GetUIntData(SqlHandle,29));
					    ((CItemFurnishing*)PItem)->setMoghancement(Sql_GetUIntData(SqlHandle,30));
					    ((CItemFurnishing*)PItem)->setElement(Sql_GetUIntData(SqlHandle,31));
					    ((CItemFurnishing*)PItem)->setAura(Sql_GetUIntData(SqlHandle,32));
				    }
				    g_pItemList[PItem->getID()] = PItem;
			    }
		    }
	    }
	
	    ret = Sql_Query(SqlHandle,"SELECT itemId, modId, value FROM item_mods WHERE itemId IN (SELECT itemId FROM item_basic LEFT JOIN item_armor USING (itemId))");
	    
	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
		    {
			    uint16 ItemID = (uint16)Sql_GetUIntData(SqlHandle,0);
			    uint16 modID  = (uint16)Sql_GetUIntData(SqlHandle,1);
			    int16  value  = (int16) Sql_GetIntData (SqlHandle,2);

			    if ((g_pItemList[ItemID] != NULL) && g_pItemList[ItemID]->isType(ITEM_ARMOR))
			    {
                    ((CItemArmor*)g_pItemList[ItemID])->addModifier(new CModifier(modID,value));
			    }
		    }
	    }

	    ret = Sql_Query(SqlHandle,"SELECT itemId, modId, value, latentId, latentParam FROM item_latents WHERE itemId IN (SELECT itemId FROM item_basic LEFT JOIN item_armor USING (itemId))");
	    
	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
		    {
			    uint16 ItemID = (uint16)Sql_GetUIntData(SqlHandle,0);
			    uint16 modID  = (uint16)Sql_GetUIntData(SqlHandle,1);
			    int16  value  = (int16) Sql_GetIntData (SqlHandle,2);
				uint16 latentId = (uint16) Sql_GetIntData(SqlHandle,3);
				uint16 latentParam = (uint16) Sql_GetIntData(SqlHandle,4);

			    if ((g_pItemList[ItemID] != NULL) && g_pItemList[ItemID]->isType(ITEM_ARMOR))
			    {
                    ((CItemArmor*)g_pItemList[ItemID])->addLatent(new CLatentEffect((LATENT)latentId, latentParam, 0, modID, value));
			    }
		    }
	    }
    }

    /************************************************************************
    *                                                                       *
    *  Загружаем списки предметов, выпадающих из монстров                   *
    *                                                                       *
    ************************************************************************/

    void LoadDropList()
    {
        int32 ret = Sql_Query(SqlHandle, "SELECT dropId, itemId, type, rate FROM mob_droplist WHERE dropid < %u;", MAX_DROPID);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
		    {
			    uint16 DropID  = (uint16)Sql_GetUIntData(SqlHandle,0);

                if (g_pDropList[DropID] == 0)
                {
                    g_pDropList[DropID] = new DropList_t;
                }

                DropItem_t DropItem;

                DropItem.ItemID  = (uint16)Sql_GetIntData(SqlHandle,1);
                DropItem.DropType = (uint8)Sql_GetIntData(SqlHandle,2);
                DropItem.DropRate = (uint16)Sql_GetIntData(SqlHandle,3);
				
                g_pDropList[DropID]->push_back(DropItem);
		    }
	    }
    }


    /************************************************************************
    *                                                                       *
    *  Handles loot from BCNM chests and other NPCs that drop things into   *
    *  the loot pool instead of adding them directly to the inventory       *
    *                                                                       *
    ************************************************************************/

    void LoadLootList()
    {
		int32 ret = Sql_Query(SqlHandle, "SELECT LootDropId, itemId, rolls, lootGroupId FROM bcnm_loot WHERE LootDropId < %u;", MAX_LOOTID);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
		    {
			    uint16 LootID  = (uint16)Sql_GetUIntData(SqlHandle,0);

                if (g_pLootList[LootID] == 0)
                {
                    g_pLootList[LootID] = new LootList_t;
                }

                LootItem_t LootItem;

                LootItem.ItemID  = (uint16)Sql_GetIntData(SqlHandle,1);
                LootItem.Rolls = (uint16)Sql_GetIntData(SqlHandle,2);
				LootItem.LootGroupId = (uint8)Sql_GetIntData(SqlHandle,3);
				
                g_pLootList[LootID]->push_back(LootItem);
		    }
		}
    }

    /************************************************************************
    *                                                                       *
    *  Инициализация системы игровых предметов                              *
    *                                                                       *
    ************************************************************************/

    void Initialize()
    {
        LoadItemList();
        LoadDropList();
        LoadLootList();

        PUnarmedItem = new CItemWeapon(0);

		PUnarmedItem->setDmgType(DAMAGE_NONE);
        PUnarmedItem->setSkillType(SKILL_NON);

        PUnarmedH2HItem = new CItemWeapon(0);

        PUnarmedH2HItem->setDmgType(DAMAGE_HTH);
        PUnarmedH2HItem->setSkillType(SKILL_H2H);
    }

    /************************************************************************
    *                                                                       *
    *  Освобождаем базу предметов (метод только для "галочки")              *
    *                                                                       *
    ************************************************************************/

    void FreeItemList()
    {
	    for(int32 ItemID = 0; ItemID < MAX_ITEMID; ++ItemID)
	    {
		    if ((g_pItemList[ItemID] != NULL) && g_pItemList[ItemID]->isType(ITEM_ARMOR))
		    {
			    CItemArmor* PItem = (CItemArmor*)g_pItemList[ItemID];

			    for (uint32 i = 0; i < PItem->modList.size(); ++i)
			    {
				    delete PItem->modList.at(i);
			    }
			    PItem->modList.clear();
		    }
		    delete g_pItemList[ItemID];
	    }

	    for(int32 DropID = 0; DropID < MAX_DROPID; ++DropID)
	    {
		    delete g_pDropList[DropID];
	    }
    }
}; // namespace itemutils



namespace nameSpaceUnlockableWeapons
{

	UnlockedWeapons_t g_pWeaponUnlockable[MAX_UNLOCKABLE_WEAPONS] = {0};


	/************************************************************************
    *                                                                       *
    *  load unlockable weapons from DB					                    *
    *                                                                       *
    ************************************************************************/

    void LoadUnlockableWeaponList()
    {
        int32 ret = Sql_Query(SqlHandle, "SELECT itemid, points FROM item_weapon_unlocked WHERE Id < %u;", MAX_UNLOCKABLE_WEAPONS);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
			uint16 index = 0;

		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS) 
			{
				UnlockedWeapons_t UnlockedWeapon = {0};

				UnlockedWeapon.itemid = Sql_GetUIntData(SqlHandle,0);
				UnlockedWeapon.required = Sql_GetUIntData(SqlHandle,1);

				g_pWeaponUnlockable[index] = UnlockedWeapon;
				index++;
		    }
	    }

    }

};