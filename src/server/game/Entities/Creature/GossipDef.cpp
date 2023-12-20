/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "QuestDef.h"
#include "GossipDef.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Formulas.h"

GossipMenu::GossipMenu()
{
    _menuId = 0;
    _senderGUID.Clear(); 
}

GossipMenu::~GossipMenu()
{
    ClearMenu();
}

void GossipMenu::AddMenuItem(int32 menuItemId, uint8 icon, std::string const& message, uint32 sender, uint32 action, std::string const& boxMessage, uint32 boxMoney, bool coded /*= false*/)
{
    ASSERT(_menuItems.size() <= GOSSIP_MAX_MENU_ITEMS);

    // Find a free new id - script case
    if (menuItemId == -1)
    {
        menuItemId = 0;
        if (!_menuItems.empty())
        {
            for (GossipMenuItemContainer::const_iterator itr = _menuItems.begin(); itr != _menuItems.end(); ++itr)
            {
                if (int32(itr->first) > menuItemId)
                    break;

                menuItemId = itr->first + 1;
            }
        }
    }

    GossipMenuItem& menuItem = _menuItems[menuItemId];

    menuItem.MenuItemIcon    = icon;
    menuItem.Message         = message;
    menuItem.IsCoded         = coded;
    menuItem.Sender          = sender;
    menuItem.OptionType      = action;
    menuItem.BoxMessage      = boxMessage;
    menuItem.BoxMoney        = boxMoney;
}

/**
 * @name AddMenuItem
 * @brief Adds a localized gossip menu item from db by menu id and menu item id.
 * @param menuId Gossip menu id.
 * @param menuItemId Gossip menu item id.
 * @param sender Identifier of the current menu.
 * @param action Custom action given to OnGossipHello.
 */
void GossipMenu::AddMenuItem(uint32 menuId, uint32 menuItemId, uint32 sender, uint32 action)
{
    /// Find items for given menu id.
    GossipMenuItemsMapBounds bounds = sObjectMgr->GetGossipMenuItemsMapBounds(menuId);
    auto itr = std::find_if(bounds.first, bounds.second, [menuItemId](std::pair<uint32 const, GossipMenuItems> const& itemPair)
    {
        return itemPair.second.OptionID == menuItemId;
    });

    if (itr == bounds.second)
        return;

    /// Store texts for localization.
    std::string strOptionText, strBoxText;
    BroadcastText const* optionBroadcastText = sObjectMgr->GetBroadcastText(itr->second.OptionBroadcastTextID);
    BroadcastText const* boxBroadcastText = sObjectMgr->GetBroadcastText(itr->second.BoxBroadcastTextID);

    /// OptionText
    if (optionBroadcastText)
        strOptionText = optionBroadcastText->GetText(GetLocale());
    else
        strOptionText = itr->second.OptionText;

    /// BoxText
    if (boxBroadcastText)
        strBoxText = boxBroadcastText->GetText(GetLocale());
    else
        strBoxText = itr->second.BoxText;

    /// Check need of localization.
    if (GetLocale() != DEFAULT_LOCALE)
    {
        if (!optionBroadcastText)
        {
            /// Find localizations from database.
            if (GossipMenuItemsLocale const* gossipMenuLocale = sObjectMgr->GetGossipMenuItemsLocale(menuId, menuItemId))
                ObjectMgr::GetLocaleString(gossipMenuLocale->OptionText, GetLocale(), strOptionText);
        }

        if (!boxBroadcastText)
        {
            /// Find localizations from database.
            if (GossipMenuItemsLocale const* gossipMenuLocale = sObjectMgr->GetGossipMenuItemsLocale(menuId, menuItemId))
                ObjectMgr::GetLocaleString(gossipMenuLocale->BoxText, GetLocale(), strBoxText);
        }
    }

    /// Add menu item with existing method. Menu item id -1 is also used in ADD_GOSSIP_ITEM macro.
    AddMenuItem(itr->second.OptionID, itr->second.OptionIcon, strOptionText, sender, action, strBoxText, itr->second.BoxMoney, itr->second.BoxCoded);
    AddGossipMenuItemData(itr->second.OptionID, itr->second.ActionMenuID, itr->second.ActionPoiID);

}

void GossipMenu::AddGossipMenuItemData(uint32 menuItemId, uint32 gossipActionMenuId, uint32 gossipActionPoi)
{
    GossipMenuItemData& itemData = _menuItemData[menuItemId];

    itemData.GossipActionMenuId  = gossipActionMenuId;
    itemData.GossipActionPoi     = gossipActionPoi;
}

uint32 GossipMenu::GetMenuItemSender(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return 0;

    return itr->second.Sender;
}

uint32 GossipMenu::GetMenuItemAction(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return 0;

    return itr->second.OptionType;
}

bool GossipMenu::IsMenuItemCoded(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return false;

    return itr->second.IsCoded;
}

void GossipMenu::ClearMenu()
{
    _menuItems.clear();
    _menuItemData.clear();
}

PlayerMenu::PlayerMenu(WorldSession* session) : _session(session)
{
    if (_session)
        _gossipMenu.SetLocale(_session->GetSessionDbLocaleIndex());
}

PlayerMenu::~PlayerMenu()
{
    ClearMenus();
}

void PlayerMenu::ClearMenus()
{
    _gossipMenu.ClearMenu();
    _questMenu.ClearMenu();
}

void PlayerMenu::SendGossipMenu(uint32 titleTextId, ObjectGuid objectGUID) const
{
    std::vector<std::string> updatedQuestTitles;
    updatedQuestTitles.reserve(_questMenu.GetMenuItemCount());

    //ObjectGuid guid = ObjectGuid(objectGUID);
    ObjectGuid guid = objectGUID;

    WorldPacket data(SMSG_GOSSIP_MESSAGE, 150);             // Guessed

    data.WriteBits(_questMenu.GetMenuItemCount(), 19);      // max count 0x20

    // Store this instead of checking the Singleton every loop iteration
    bool questLevelInTitle = sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS);

    for (uint8 i = 0; i < _questMenu.GetMenuItemCount(); ++i)
    {
        uint32 questId = _questMenu.GetItem(i).QuestId;
        Quest const* quest = sObjectMgr->GetQuestTemplate(questId);

        std::string title = quest->GetTitle();

        LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
        if (localeConstant != LOCALE_enUS)
            if (QuestTemplateLocale const* localeData = sObjectMgr->GetQuestLocale(questId))
                ObjectMgr::GetLocaleString(localeData->LogTitle, localeConstant, title);

        if (questLevelInTitle)
            AddQuestLevelToTitle(title, quest->GetQuestLevel());

        data.WriteBit(quest->IsRepeatable());               // 3.3.3 changes icon: (0) yellow exclamation or (1) blue question
        data.WriteBits(title.length(), 9);

        updatedQuestTitles.push_back(title);
    }

    data.WriteBit(guid[5]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[0]);
    data.WriteBits(_gossipMenu.GetMenuItemCount(), 20);     // max count 0x10
    data.WriteBit(guid[6]);
    data.WriteBit(guid[2]);

    for (GossipMenuItemContainer::const_iterator itr = _gossipMenu.GetMenuItems().begin(); itr != _gossipMenu.GetMenuItems().end(); ++itr)
    {
        GossipMenuItem const& item = itr->second;

        data.WriteBits(item.BoxMessage.length(), 12);
        data.WriteBits(item.Message.length(), 12);
    }

    data.WriteBit(guid[3]);
    data.WriteBit(guid[1]);
    data.FlushBits();

    for (uint8 i = 0; i < _questMenu.GetMenuItemCount(); ++i)
    {
        QuestMenuItem const& item = _questMenu.GetItem(i);
        Quest const* quest = sObjectMgr->GetQuestTemplate(item.QuestId);

        data.WriteString(updatedQuestTitles[i]);
        data << int32(quest->GetFlags());
        data << int32(quest->GetQuestLevel());
        data << int32(item.QuestIcon);
        data << int32(item.QuestId);
        data << int32(quest->GetFlags2());
    }

    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[0]);

    for (GossipMenuItemContainer::const_iterator itr = _gossipMenu.GetMenuItems().begin(); itr != _gossipMenu.GetMenuItems().end(); ++itr)
    {
        GossipMenuItem const& item = itr->second;

        data << int32(item.BoxMoney);                       // money required to open menu, 2.0.3
        data.WriteString(item.BoxMessage);                  // accept text (related to money) pop up box, 2.0.
        data << int32(itr->first);
        data << int8(item.IsCoded);                         // makes pop up box password
        data.WriteString(item.Message);                     // text for gossip item
        data << int8(item.MenuItemIcon);
    }

    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[3]);
    data << int32(_gossipMenu.GetMenuId());                 // new 2.4.0
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[4]);
    data << int32(0);                                       // friend faction ID?
    data.WriteByteSeq(guid[7]);
    data << int32(titleTextId);

    _session->SendPacket(&data);
}

void PlayerMenu::SendCloseGossip() const
{
    //_gossipMenu.SetSenderGUID(ObjectGuid::Empty);
    WorldPacket data(SMSG_GOSSIP_COMPLETE, 0);
    _session->SendPacket(&data);
}

void PlayerMenu::SendPointOfInterest(uint32 poiId) const
{
    PointOfInterest const* poi = sObjectMgr->GetPointOfInterest(poiId);
    if (!poi)
    {
        TC_LOG_ERROR("sql.sql", "Request to send non-existing POI (Id: %u), ignored.", poiId);
        return;
    }

    std::string iconText = poi->icon_name;
    LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
    if (localeConstant != LOCALE_enUS)
        if (PointOfInterestLocale const* localeData = sObjectMgr->GetPointOfInterestLocale(poiId))
            ObjectMgr::GetLocaleString(localeData->IconName, localeConstant, iconText);

    WorldPacket data(SMSG_GOSSIP_POI, 4 + 4 + 4 + 4 + 4 + 10);  // guess size
    data << uint32(poi->flags);
    data << float(poi->x);
    data << float(poi->y);
    data << uint32(poi->icon);
    data << uint32(poi->data);
    data << iconText;

    _session->SendPacket(&data);
}

/*********************************************************/
/***                    QUEST SYSTEM                   ***/
/*********************************************************/

QuestMenu::QuestMenu()
{
    _questMenuItems.reserve(16);                                   // can be set for max from most often sizes to speedup push_back and less memory use
}

QuestMenu::~QuestMenu()
{
    ClearMenu();
}

void QuestMenu::AddMenuItem(uint32 QuestId, uint8 Icon)
{
    if (!sObjectMgr->GetQuestTemplate(QuestId))
        return;

    ASSERT(_questMenuItems.size() <= GOSSIP_MAX_MENU_ITEMS);

    QuestMenuItem questMenuItem;

    questMenuItem.QuestId        = QuestId;
    questMenuItem.QuestIcon      = Icon;

    _questMenuItems.push_back(questMenuItem);
}

bool QuestMenu::HasItem(uint32 questId) const
{
    for (QuestMenuItemList::const_iterator i = _questMenuItems.begin(); i != _questMenuItems.end(); ++i)
        if (i->QuestId == questId)
            return true;

    return false;
}

void QuestMenu::ClearMenu()
{
    _questMenuItems.clear();
}

void PlayerMenu::SendQuestGiverQuestList(QEmote eEmote, const std::string& Title, uint64 npcGUID)
{
    ByteBuffer questData;
    ObjectGuid guid = npcGUID;

    WorldPacket data(SMSG_QUESTGIVER_QUEST_LIST, 100);      // guess size
    data << uint32(eEmote._Emote);                          // NPC emote
    data << uint32(eEmote._Delay);                          // player emote

    data.WriteBit(guid[2]);
    data.WriteBits(Title.size(), 11);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[0]);

    uint32 count = 0;
    size_t countPos = data.bitwpos();
    data.WriteBits(count, 19);

    // Store this instead of checking the Singleton every loop iteration
    bool questLevelInTitle = sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS);

    for (uint32 i = 0; i < _questMenu.GetMenuItemCount(); ++i)
    {
        QuestMenuItem const& qmi = _questMenu.GetItem(i);

        uint32 questID = qmi.QuestId;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(questID))
        {
            ++count;
            std::string title = quest->GetTitle();

            LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
            if (localeConstant != LOCALE_enUS)
                if (QuestTemplateLocale const* localeData = sObjectMgr->GetQuestLocale(questID))
                    ObjectMgr::GetLocaleString(localeData->LogTitle, localeConstant, title);

            if (questLevelInTitle)
                AddQuestLevelToTitle(title, quest->GetQuestLevel());

            data.WriteBit(quest->IsRepeatable());           // 3.3.3 changes icon: (0) yellow exclamation or (1) blue question
            data.WriteBits(title.size(), 9);

            questData << uint32(quest->GetFlags());
            questData << uint32(questID);
            questData.WriteString(title);
            questData << uint32(quest->GetFlags2());
            questData << uint32(qmi.QuestIcon);
            questData << uint32(quest->GetQuestLevel());
        }
    }

    data.WriteBit(guid[1]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[7]);
    data.PutBits(countPos, count, 19);
    data.FlushBits();

    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[7]);
    data.append(questData);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[2]);
    data.WriteString(Title);
    data.WriteByteSeq(guid[4]);

    _session->SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUESTGIVER_QUEST_LIST NPC Guid=%u", GUID_LOPART(npcGUID));
}

void PlayerMenu::SendQuestGiverStatus(uint32 questStatus, uint64 npcGUID) const
{
    ObjectGuid guid = npcGUID;

    WorldPacket data(SMSG_QUESTGIVER_STATUS, 1 + 8 + 4);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[0]);

    data.WriteByteSeq(guid[7]);
    data << uint32(questStatus);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[3]);

    _session->SendPacket(&data);
    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUESTGIVER_STATUS NPC Guid=%u, status=%u", GUID_LOPART(npcGUID), questStatus);
}

void PlayerMenu::SendQuestGiverQuestDetails(Quest const* quest, uint64 npcGUID, bool activateAccept, bool startedByAreaTrigger) const
{

    std::string questTitle           = quest->GetTitle();
    std::string questDetails         = quest->GetDetails();
    std::string questObjectives      = quest->GetObjectives();
    std::string questGiverTextWindow = quest->GetQuestGiverTextWindow();
    std::string questGiverTargetName = quest->GetQuestGiverTargetName();
    std::string questTurnTextWindow  = quest->GetQuestTurnTextWindow();
    std::string questTurnTargetName  = quest->GetQuestTurnTargetName();

    LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
    if (localeConstant != LOCALE_enUS)
    {
        if (QuestTemplateLocale const* localeData = sObjectMgr->GetQuestLocale(quest->GetQuestId()))
        {
            ObjectMgr::GetLocaleString(localeData->LogTitle, localeConstant, questTitle);
            ObjectMgr::GetLocaleString(localeData->QuestDescription, localeConstant, questDetails);
            ObjectMgr::GetLocaleString(localeData->LogDescription, localeConstant, questObjectives);
            ObjectMgr::GetLocaleString(localeData->PortraitGiverText, localeConstant, questGiverTextWindow);
            ObjectMgr::GetLocaleString(localeData->PortraitGiverName, localeConstant, questGiverTargetName);
            ObjectMgr::GetLocaleString(localeData->PortraitTurnInText, localeConstant, questTurnTextWindow);
            ObjectMgr::GetLocaleString(localeData->PortraitTurnInName, localeConstant, questTurnTargetName);
        }
    }

    if (sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS))
        AddQuestLevelToTitle(questTitle, quest->GetQuestLevel());

    ByteBuffer objData;
    for (QuestObjectiveSet::const_iterator citr = quest->m_questObjectives.begin(); citr != quest->m_questObjectives.end(); citr++)
    {
        QuestObjective const* objective = *citr;
        objData << uint8(objective->Type);
        objData << uint32(objective->Id);
        objData << int32(objective->Amount);
        objData << uint32(objective->ObjectId);
    }

    uint32 rewItemDisplayId[QUEST_REWARDS_COUNT];
    uint32 rewChoiceItemDisplayId[QUEST_REWARD_CHOICES_COUNT];

    std::vector<std::pair<uint32 /*itemId*/, uint32 /*count*/>> rewInfo;
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; i++)
    {
        uint32 id = quest->RewardItemId[i];
        uint32 count = quest->RewardItemIdCount[i];

        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(id))
            rewItemDisplayId[i] = itemTemplate->DisplayInfoID;
        else
            rewItemDisplayId[i] = 0;

        rewInfo.push_back(std::make_pair(id, count));
    }

    for (uint8 i = 0; i < QUEST_REWARD_CHOICES_COUNT; i++)
    {
        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(quest->RewardChoiceItemId[i]))
            rewChoiceItemDisplayId[i] = itemTemplate->DisplayInfoID;
        else
            rewChoiceItemDisplayId[i] = 0;
    }

    ObjectGuid guid2 = npcGUID;
    ObjectGuid guid = _session->GetPlayer()->GetDivider();

    WorldPacket data(SMSG_QUESTGIVER_QUEST_DETAILS, 100);   // guess size
    data << uint32(rewInfo[3].second);
    data << uint32(rewChoiceItemDisplayId[4]);
    data << uint32(quest->RewardChoiceItemId[2]);

    for (uint8 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; i++)
    {
        data << uint32(quest->RewardCurrencyCount[i]);
        data << uint32(quest->RewardCurrencyId[i]);
    }

    data << uint32(quest->GetRewChoiceItemsCount());
    data << uint32(quest->RewardChoiceItemCount[2]);
    data << uint32(rewInfo[1].second);
    data << uint32(rewChoiceItemDisplayId[5]);
    data << uint32(rewInfo[0].second);
    data << uint32(rewItemDisplayId[3]);
    data << uint32(quest->RewardChoiceItemId[0]);
    data << uint32(quest->RewardChoiceItemCount[3]);
    data << uint32(quest->GetQuestGiverPortrait());
    data << uint32(rewChoiceItemDisplayId[3]);
    data << uint32(rewInfo[0].first);
    data << uint32(quest->GetQuestId());
    data << uint32(quest->GetSuggestedPlayers());
    data << uint32(rewChoiceItemDisplayId[0]);
    data << uint32(quest->RewardChoiceItemCount[4]);
    data << uint32(quest->RewardChoiceItemCount[5]);
    data << uint32(quest->GetBonusTalents());
    data << uint32(quest->RewardChoiceItemCount[1]);
    data << uint32(rewChoiceItemDisplayId[2]);

    for (uint8 i = 0; i < QUEST_REPUTATIONS_COUNT; i++)
    {
        data << uint32(quest->RewardFactionValueId[i]);
        data << uint32(quest->RewardFactionValueIdOverride[i]);
        data << uint32(quest->RewardFactionId[i]);
    }

    data << uint32(rewInfo[3].first);
    data << uint32(quest->GetRewardSkillId());
    data << uint32(quest->XPValue(_session->GetPlayer()) * sWorld->getRate(RATE_XP_QUEST));
    data << uint32(quest->GetRewardReputationMask());
    data << uint32(rewItemDisplayId[2]);
    data << uint32(rewInfo[1].first);
    data << uint32(quest->RewardChoiceItemId[1]);
    data << uint32(quest->RewardChoiceItemId[5]);
    data << uint32(quest->GetRewSpell());
    data << uint32(quest->GetFlags());
    data << uint32(quest->GetCharTitleId());
    data << uint32(rewInfo[2].first);
    data << uint32(quest->GetRewardOrRequiredMoney());
    data << uint32(rewInfo[2].second);
    data << uint32(quest->GetFlags2());
    data << uint32(0); // should be quest->GetRewSpellCast(), but need to know in which cases this need sends
    data << uint32(quest->RewardChoiceItemId[3]);
    data << uint32(quest->GetRewItemsCount());
    data << uint32(quest->GetRewardSkillPoints());
    data << uint32(rewItemDisplayId[0]);
    data << uint32(quest->RewardChoiceItemId[4]);
    data << uint32(quest->GetRewardPackageItemId());
    data << uint32(quest->RewardChoiceItemCount[0]);
    data << uint32(rewItemDisplayId[1]);
    data << uint32(rewChoiceItemDisplayId[1]);
    data << uint32(quest->GetQuestTurnInPortrait());

    data.WriteBit(guid[7]);
    data.WriteBit(guid2[1]);
    data.WriteBits(questTurnTargetName.size(), 8);
    data.WriteBit(guid2[2]);
    data.WriteBits(questGiverTextWindow.size(), 10);
    data.WriteBit(startedByAreaTrigger);
    data.WriteBit(guid[2]);
    data.WriteBits(questTitle.size(), 9);
    data.WriteBits(QUEST_EMOTE_COUNT, 21);
    data.WriteBit(guid[0]);
    data.WriteBit(guid2[6]);
    data.WriteBit(guid2[5]);
    data.WriteBits(questGiverTargetName.size(), 8);
    data.WriteBit(guid2[3]);
    data.WriteBit(guid[1]);
    data.WriteBit(guid2[0]);
    data.WriteBit(0);                                       // CGQuestInfo::m_startQuestCheat
    data.WriteBit(guid2[4]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[4]);
    data.WriteBits(questTurnTextWindow.size(), 10);
    data.WriteBit(activateAccept);                          // CGQuestInfo::m_autoLaunched
    data.WriteBit(guid[6]);
    data.WriteBit(guid2[7]);
    data.WriteBits(questDetails.size(), 12);
    data.WriteBits(0, 22);                                  // LearnSpellsCount
    data.WriteBits(quest->m_questObjectives.size(), 20);
    data.WriteBits(questObjectives.size(), 12);
    data.FlushBits();

    data.WriteByteSeq(guid[0]);
    data.WriteString(questGiverTargetName);
    data.WriteString(questTurnTextWindow);
    data.WriteString(questTitle);
    data.WriteByteSeq(guid2[6]);
    data.WriteString(questObjectives);
    data.WriteByteSeq(guid[2]);
    data.WriteString(questGiverTextWindow);
    data.append(objData);
    data.WriteString(questTurnTargetName);
    data.WriteString(questDetails);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid2[7]);
    data.WriteByteSeq(guid2[3]);
    data.WriteByteSeq(guid2[0]);

    for (uint8 i = 0; i < QUEST_EMOTE_COUNT; i++)
    {
        data << uint32(quest->DetailsEmoteDelay[i]);        // DetailsEmoteDelay (in ms)
        data << uint32(quest->DetailsEmote[i]);
    }

    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid2[5]);
    data.WriteByteSeq(guid2[1]);
    data.WriteByteSeq(guid2[2]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid2[4]);

    /*for (uint i = 0; i < unkCounterBits22; i++)
        data << uint32(0);*/ // LearnSpells

    _session->SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUESTGIVER_QUEST_DETAILS NPCGuid=%u, questid=%u", GUID_LOPART(npcGUID), quest->GetQuestId());
}

void PlayerMenu::SendQuestQueryResponse(Quest const* quest) const
{

    std::string questTitle = quest->GetTitle();
    std::string questDetails = quest->GetDetails();
    std::string questObjectives = quest->GetObjectives();
    std::string questEndText = quest->GetEndText();
    std::string questCompletedText = quest->GetCompletedText();
    std::string questGiverTextWindow = quest->GetQuestGiverTextWindow();
    std::string questGiverTargetName = quest->GetQuestGiverTargetName();
    std::string questTurnTextWindow = quest->GetQuestTurnTextWindow();
    std::string questTurnTargetName = quest->GetQuestTurnTargetName();

    LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
    if (localeConstant != LOCALE_enUS)
    {
        if (QuestTemplateLocale const* localeData = sObjectMgr->GetQuestLocale(quest->GetQuestId()))
        {
            ObjectMgr::GetLocaleString(localeData->LogTitle, localeConstant, questTitle);
            ObjectMgr::GetLocaleString(localeData->QuestDescription, localeConstant, questDetails);
            ObjectMgr::GetLocaleString(localeData->LogDescription, localeConstant, questObjectives);
            ObjectMgr::GetLocaleString(localeData->AreaDescription, localeConstant, questEndText);
            ObjectMgr::GetLocaleString(localeData->QuestCompletionLog, localeConstant, questCompletedText);
            ObjectMgr::GetLocaleString(localeData->PortraitGiverText, localeConstant, questGiverTextWindow);
            ObjectMgr::GetLocaleString(localeData->PortraitGiverName, localeConstant, questGiverTargetName);
            ObjectMgr::GetLocaleString(localeData->PortraitTurnInText, localeConstant, questTurnTextWindow);
            ObjectMgr::GetLocaleString(localeData->PortraitTurnInName, localeConstant, questTurnTargetName);            
        }

    }

    std::vector<std::pair<uint32 /*itemId*/, uint32 /*count*/>> rewInfo;
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; i++)
    {
        uint32 id = quest->RewardItemId[i];
        uint32 count = quest->RewardItemIdCount[i];

        rewInfo.push_back(std::make_pair(id, count));
    }

    if (sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS))
        AddQuestLevelToTitle(questTitle, quest->GetQuestLevel());

    WorldPacket data(SMSG_QUEST_QUERY_RESPONSE, 100);   // guess size
    data << uint32(quest->GetQuestId());

    data.WriteBit(1);                                   // has data
    data.WriteBits(questTurnTextWindow.size(), 10);
    data.WriteBits(questTitle.size(), 9);
    data.WriteBits(questCompletedText.size(), 11);
    data.WriteBits(questDetails.size(), 12);
    data.WriteBits(questTurnTargetName.size(), 8);
    data.WriteBits(questGiverTargetName.size(), 8);
    data.WriteBits(questGiverTextWindow.size(), 10);
    data.WriteBits(questEndText.size(), 9);
    data.WriteBits(quest->m_questObjectives.size(), 19);
    data.WriteBits(questObjectives.size(), 12);

    ByteBuffer objData;
    for (QuestObjectiveSet::const_iterator citr = quest->m_questObjectives.begin(); citr != quest->m_questObjectives.end(); citr++)
    {
        QuestObjective const* questObjective = *citr;

        std::string descriptionText = questObjective->Description;
        if (localeConstant != LOCALE_enUS)
            if (QuestObjectivesLocale const* questObjectiveLocale = sObjectMgr->GetQuestObjectivesLocale(questObjective->Id))
            //if (QuestObjectiveLocale const* questObjectiveLocale = sObjectMgr->GetQuestObjectiveLocale(questObjective->Id))
                ObjectMgr::GetLocaleString(questObjectiveLocale->Description, localeConstant, descriptionText);

        data.WriteBits(descriptionText.size(), 8);
        data.WriteBits(questObjective->VisualEffects.size(), 22);

        objData << int32(questObjective->Amount);
        objData << uint32(questObjective->Id);
        objData.WriteString(descriptionText);
        objData << uint32(questObjective->Flags);
        objData << int8(questObjective->Index);
        objData << uint8(questObjective->Type);
        objData << uint32(questObjective->ObjectId);

        for (VisualEffectVec::const_iterator citrEffects = questObjective->VisualEffects.begin(); citrEffects != questObjective->VisualEffects.end(); citrEffects++)
            objData << uint32(*citrEffects);
    }

    data.FlushBits();

    bool hiddenReward = quest->HasFlag(QUEST_FLAGS_HIDDEN_REWARDS);

    // values need rechecking and zero values need more research
    data.append(objData);
    data << uint32(quest->RequiredSourceItemId[0]);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[4]);
    data << uint32(hiddenReward ? 0 : rewInfo[3].first);
    data << uint32(hiddenReward ? 0 : rewInfo[1].second);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[2]);

    for (uint32 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; i++)
    {
        data << uint32(quest->RewardCurrencyId[i]);
        data << uint32(quest->RewardCurrencyCount[i]);
    }

    data << uint32(quest->GetBonusTalents());                               // bonus talents
    data << float(quest->GetPointY());
    data << uint32(quest->GetSoundTurnIn());

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; i++)
    {
        data << uint32(quest->RewardFactionValueIdOverride[i]);             // unknown usage
        data << uint32(quest->RewardFactionValueId[i]);                     // columnid+1 QuestFactionReward.dbc?
        data << uint32(quest->RewardFactionId[i]);                          // reward factions ids
    }

    data << uint32(hiddenReward ? 0 : quest->GetRewardOrRequiredMoney());                // reward money (below max lvl)
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[4]);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[1]);
    data << uint32(quest->GetFlags2());
    data.WriteString(questEndText);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[1]);
    data << uint32(quest->GetRewMoneyMaxLevel());                           // used in XP calculation at client
    data << uint32(hiddenReward ? 0 : rewInfo[0].first);
    data.WriteString(questCompletedText);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[3]);
    data << uint32(quest->GetRewHonorAddition());                           // rewarded honor points
    data.WriteString(questGiverTextWindow);
    data.WriteString(questObjectives);
    data << uint32(quest->GetRewardSkillPoints());                          // reward skill points
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[5]);
    data << uint32(quest->GetSuggestedPlayers());                           // suggested players count
    data << uint32(quest->GetQuestId());                                    // quest id
    data << uint32(quest->RequiredSourceItemId[1]);
    data << uint32(hiddenReward ? 0 : rewInfo[1].first);
    data << int32(quest->GetMinLevel());                                    // min level
    data << uint32(quest->GetRewardReputationMask());                       // rep mask (unsure on what it does)
    data << uint32(quest->GetPointOpt());
    data << int32(quest->GetQuestLevel());                                  // may be -1, static data, in other cases must be used dynamic level: Player::GetQuestLevel (0 is not known, but assuming this is no longer valid for quest intended for client)
    data << uint32(quest->GetQuestMethod());                                // Accepted values: 0, 1 or 2. 0 == IsAutoComplete() (skip objectives/details)
    data << uint32(quest->RequiredSourceItemCount[2]);
    data << uint32(quest->GetXPId());                                       // seems to always have the same value as the first XP ID field
    data.WriteString(questDetails);
    data << uint32(hiddenReward ? 0 : rewInfo[0].second);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[5]);
    data << uint32(hiddenReward ? 0 : rewInfo[2].second);
    data << uint32(0);                                                      // casted spell (quest->GetRewSpellCast() (see above))
    data << uint32(0);                                                      // unknown
    data.WriteString(questTurnTargetName);
    data << uint32(0);                                                      // unknown
    data << uint32(quest->RequiredSourceItemCount[1]);
    data << uint32(quest->RequiredSourceItemId[2]);
    data << uint32(quest->GetQuestTurnInPortrait());
    data.WriteString(questTitle);
    data << uint32(quest->GetType());                                       // quest type
    data << uint32(quest->GetXPId());                                       // used for calculating rewarded experience
    data << uint32(0);                                                      // unknown
    data << uint32(0);                                                      // unknown
    data << uint32(quest->GetPointMapId());
    data << uint32(quest->GetNextQuestInChain());                           // client will request this quest from NPC, if not 0
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[0]);
    data.WriteString(questGiverTargetName);
    data << uint32(0);                                                      // unknown
    data << uint32(quest->RequiredSourceItemId[3]);
    data << float(quest->GetPointX());
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemId[2]);
    data << uint32(0);                                                      // unknown
    data << uint32(hiddenReward ? 0 : rewInfo[3].second);
    data << uint32(quest->GetSoundAccept());
    data << uint32(hiddenReward ? 0 : rewInfo[2].first);
    data << float(quest->GetRewHonorMultiplier());
    data << uint32(quest->GetCharTitleId());                                // CharTitleId, new 2.4.0, player gets this title (id from CharTitles)
    data.WriteString(questTurnTextWindow);
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[3]);
    data << uint32(quest->RequiredSourceItemCount[0]);
    data << int32(quest->GetZoneOrSort());                                  // zone or sort to display in quest log
    data << uint32(quest->GetRewardSkillId());                              // reward skill id
    data << uint32(hiddenReward ? 0 : quest->RewardChoiceItemCount[0]);
    data << uint32(quest->GetRewSpell());                                   // reward spell, this spell will display (icon) (casted if RewSpellCast == 0)
    data << uint32(quest->GetQuestGiverPortrait());
    data << uint32(0);                                                      // unknown
    data << uint32(quest->RequiredSourceItemCount[3]);
    data << uint32(quest->GetFlags());                                      // quest flags
    data << uint32(quest->GetRewardPackageItemId());
    data << uint32(quest->GetSrcItemId());                                  // source item id

    _session->SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUEST_QUERY_RESPONSE questid=%u", quest->GetQuestId());
}

void PlayerMenu::SendQuestGiverOfferReward(Quest const* quest, uint64 npcGuid, bool enableNext) const
{

    std::string questTitle = quest->GetTitle();
    std::string questOfferRewardText = quest->GetOfferRewardText();
    std::string questGiverTextWindow = quest->GetQuestGiverTextWindow();
    std::string questGiverTargetName = quest->GetQuestGiverTargetName();
    std::string questTurnTextWindow = quest->GetQuestTurnTextWindow();
    std::string questTurnTargetName = quest->GetQuestTurnTargetName();

    LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
    if (localeConstant != LOCALE_enUS)
    {
        if (QuestTemplateLocale const* questTemplateLocale = sObjectMgr->GetQuestLocale(quest->GetQuestId()))
        {
            ObjectMgr::GetLocaleString(questTemplateLocale->LogTitle,           localeConstant, questTitle);
            ObjectMgr::GetLocaleString(questTemplateLocale->PortraitGiverText,  localeConstant, questGiverTextWindow);
            ObjectMgr::GetLocaleString(questTemplateLocale->PortraitGiverName,  localeConstant, questGiverTargetName);
            ObjectMgr::GetLocaleString(questTemplateLocale->PortraitTurnInText, localeConstant, questTurnTextWindow);
            ObjectMgr::GetLocaleString(questTemplateLocale->PortraitTurnInName, localeConstant, questTurnTargetName);            
        }

        if (QuestOfferRewardLocale const* questOfferRewardLocale = sObjectMgr->GetQuestOfferRewardLocale(quest->GetQuestId()))
            ObjectMgr::GetLocaleString(questOfferRewardLocale->RewardText, localeConstant, questOfferRewardText);
    }

    if (sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS))
        AddQuestLevelToTitle(questTitle, quest->GetQuestLevel());

    std::vector<std::pair<uint32 /*itemId*/, uint32 /*count*/>> rewInfo;
    uint32 rewItemDisplayId[QUEST_REWARDS_COUNT];
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; i++)
    {
        uint32 id = quest->RewardItemId[i];
        uint32 count = quest->RewardItemIdCount[i];

        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(id);
        rewItemDisplayId[i] = itemTemplate ? itemTemplate->DisplayInfoID : 0;

        rewInfo.push_back(std::make_pair(id, count));
    }

    uint32 rewChoiceItemDisplayId[QUEST_REWARD_CHOICES_COUNT];
    for (uint8 i = 0; i < QUEST_REWARD_CHOICES_COUNT; i++)
    {
        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(quest->RewardChoiceItemId[i]);
        rewChoiceItemDisplayId[i] = itemTemplate ? itemTemplate->DisplayInfoID : 0;
    }

    uint32 rewEmoteCount = 0;
    for (uint8 i = 0; i < QUEST_EMOTE_COUNT; i++)
    {
        if (quest->OfferRewardEmote[i] <= 0)
            break;

        rewEmoteCount++;
    }

    uint32 questEnderEntry = 0;
    if (npcGuid)
        if (Object* object = ObjectAccessor::GetObjectByTypeMask(*(_session->GetPlayer()), npcGuid, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM))
            if (object->hasInvolvedQuest(quest->GetQuestId()))
                questEnderEntry = object->GetEntry();

    ObjectGuid guid = npcGuid;

    WorldPacket data(SMSG_QUESTGIVER_OFFER_REWARD, 50);     // guess size
    data << uint32(rewInfo[2].second);
    data << uint32(quest->GetQuestId());
    data << uint32(rewInfo[3].first);
    data << uint32(rewChoiceItemDisplayId[2]);

    for (uint8 i = 0; i < QUEST_REPUTATIONS_COUNT; i++)
    {
        data << uint32(quest->RewardFactionId[i]);
        data << uint32(quest->RewardFactionValueId[i]);
        data << uint32(quest->RewardFactionValueIdOverride[i]);
    }

    data << uint32(rewInfo[0].second);
    data << uint32(rewInfo[3].second);
    data << uint32(rewItemDisplayId[3]);
    data << uint32(rewInfo[1].first);
    data << uint32(quest->RewardChoiceItemId[3]);
    data << uint32(rewChoiceItemDisplayId[3]);
    data << uint32(quest->GetRewChoiceItemsCount());
    data << uint32(0); // quest->GetRewSpellCast() (see above)
    data << uint32(rewItemDisplayId[1]);
    data << uint32(quest->RewardChoiceItemCount[5]);
    data << uint32(rewChoiceItemDisplayId[4]);
    data << uint32(quest->RewardChoiceItemCount[1]);
    data << uint32(rewChoiceItemDisplayId[0]);
    data << uint32(rewItemDisplayId[0]);
    data << uint32(quest->GetRewardPackageItemId());
    data << uint32(quest->GetQuestTurnInPortrait());
    data << uint32(rewInfo[1].second);
    data << uint32(quest->GetRewardReputationMask());
    data << uint32(quest->RewardChoiceItemId[0]);
    data << uint32(quest->RewardChoiceItemCount[3]);
    data << uint32(quest->RewardChoiceItemCount[4]);
    data << uint32(quest->RewardChoiceItemId[1]);
    data << uint32(quest->GetBonusTalents());
    data << uint32(quest->GetRewardSkillId());

    for (uint8 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; i++)
    {
        data << uint32(quest->RewardCurrencyId[i]);
        data << uint32(quest->RewardCurrencyCount[i]);
    }

    data << uint32(quest->GetFlags());
    data << uint32(quest->GetFlags2());
    data << uint32(quest->XPValue(_session->GetPlayer()) * sWorld->getRate(RATE_XP_QUEST));
    data << uint32(quest->GetCharTitleId());
    data << uint32(quest->RewardChoiceItemId[2]);
    data << uint32(quest->GetRewItemsCount());
    data << uint32(quest->GetSuggestedPlayers());
    data << uint32(quest->RewardChoiceItemId[4]);
    data << uint32(questEnderEntry);
    data << uint32(rewInfo[2].first);
    data << uint32(quest->RewardChoiceItemCount[0]);
    data << uint32(quest->GetRewardSkillPoints());
    data << uint32(quest->GetQuestGiverPortrait());
    data << uint32(quest->GetRewardOrRequiredMoney());
    data << uint32(quest->RewardChoiceItemId[5]);
    data << uint32(rewChoiceItemDisplayId[1]);
    data << uint32(quest->RewardChoiceItemCount[2]);
    data << uint32(rewItemDisplayId[2]);
    data << uint32(quest->GetRewSpell());
    data << uint32(rewInfo[0].first);
    data << uint32(rewChoiceItemDisplayId[5]);

    data.WriteBits(questTurnTextWindow.size(), 10);
    data.WriteBits(questGiverTargetName.size(), 8);
    data.WriteBit(guid[6]);
    data.WriteBits(rewEmoteCount, 21);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[7]);
    data.WriteBits(questTitle.size(), 9);
    data.WriteBit(guid[4]);
    data.WriteBits(questTurnTargetName.size(), 8);
    data.WriteBits(questGiverTextWindow.size(), 10);
    data.WriteBits(questOfferRewardText.size(), 12);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[5]);
    data.WriteBit(enableNext);
    data.FlushBits();

    data.WriteString(questGiverTargetName);
    data.WriteString(questTitle);

    for (uint8 i = 0; i < rewEmoteCount; i++)
    {
        data << uint32(quest->OfferRewardEmoteDelay[i]);
        data << uint32(quest->OfferRewardEmote[i]);
    }

    data.WriteByteSeq(guid[2]);
    data.WriteString(questOfferRewardText);
    data.WriteString(questTurnTextWindow);
    data.WriteString(questTurnTargetName);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[1]);
    data.WriteString(questGiverTextWindow);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[3]);

    _session->SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUESTGIVER_OFFER_REWARD NPCGuid=%u, questid=%u", GUID_LOPART(npcGuid), quest->GetQuestId());
}

void PlayerMenu::SendQuestGiverRequestItems(Quest const* quest, uint64 npcGuid, bool canComplete, bool closeOnCancel) const
{
    // We can always call to RequestItems, but this packet only goes out if there are actually
    // items.  Otherwise, we'll skip straight to the OfferReward

    uint32 itemCounter = quest->GetQuestObjectiveCountType(QUEST_OBJECTIVE_TYPE_ITEM);
    if (!itemCounter && canComplete)
    {
        SendQuestGiverOfferReward(quest, npcGuid, true);
        return;
    }

    std::string questTitle = quest->GetTitle();
    std::string requestItemsText = quest->GetRequestItemsText();

    LocaleConstant localeConstant = _session->GetSessionDbLocaleIndex();
    if (localeConstant != LOCALE_enUS)
    {
        if (QuestTemplateLocale const* questTemplateLocale = sObjectMgr->GetQuestLocale(quest->GetQuestId()))
            ObjectMgr::GetLocaleString(questTemplateLocale->LogTitle, localeConstant, questTitle);

        if (QuestRequestItemsLocale const* questRequestItemsLocale = sObjectMgr->GetQuestRequestItemsLocale(quest->GetQuestId()))
            ObjectMgr::GetLocaleString(questRequestItemsLocale->CompletionText, localeConstant, requestItemsText);        
    }

    uint32 requiredMoney = 0;
    ByteBuffer currencyData, itemData;

    for (QuestObjectiveSet::const_iterator citr = quest->m_questObjectives.begin(); citr != quest->m_questObjectives.end(); citr++)
    {
        QuestObjective const* questObjective = *citr;
        switch (questObjective->Type)
        {
            case QUEST_OBJECTIVE_TYPE_ITEM:
            {
                ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(questObjective->ObjectId);

                itemData << uint32(itemTemplate ? itemTemplate->DisplayInfoID : 0);
                itemData << uint32(questObjective->ObjectId);
                itemData << uint32(questObjective->Amount);
                break;
            }
            case QUEST_OBJECTIVE_TYPE_CURRENCY:
            {
                currencyData << uint32(questObjective->Amount);
                currencyData << uint32(questObjective->ObjectId);
                break;
            }
            case QUEST_OBJECTIVE_TYPE_MONEY:
            {
                requiredMoney = questObjective->Amount;
                break;
            }
            default:
                break;
        }
    }

    if (sWorld->getBoolConfig(CONFIG_UI_QUESTLEVELS_IN_DIALOGS))
        AddQuestLevelToTitle(questTitle, quest->GetQuestLevel());

    ObjectGuid guid = npcGuid;
    uint32 currencyCounter = quest->GetQuestObjectiveCountType(QUEST_OBJECTIVE_TYPE_CURRENCY);

    uint32 questGiverEntry = 0;
    if (npcGuid)
        if (Object* object = ObjectAccessor::GetObjectByTypeMask(*(_session->GetPlayer()), npcGuid, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM))
            if (object->hasInvolvedQuest(quest->GetQuestId()))
                questGiverEntry = object->GetEntry();

    WorldPacket data(SMSG_QUESTGIVER_REQUEST_ITEMS, 4 + 4 + 4 + 4 + 4 + 4 + 4 + 4 + 4 + 1 + 8 + 8 +
        questTitle.size() + requestItemsText.size() + itemCounter * (4 + 4 + 4) + currencyCounter * (4 + 4));

    data << uint32(quest->GetSuggestedPlayers());
    data << uint32(quest->GetFlags());
    data << uint32(0);                         // emote delay
    data << uint32(canComplete ? 0x5F : 0x5B); // status flags
    data << uint32(requiredMoney);
    data << uint32(questGiverEntry);
    data << uint32(quest->GetFlags2());
    data << uint32(canComplete ? quest->GetCompleteEmote() : quest->GetIncompleteEmote());
    data << uint32(quest->GetQuestId());

    data.WriteBits(currencyCounter, 21);
    data.WriteBit(closeOnCancel);
    data.WriteGuidMask(guid, 2, 5, 1);
    data.WriteBits(questTitle.size(), 9);
    data.WriteBits(requestItemsText.size(), 12);
    data.WriteGuidMask(guid, 6, 0);
    data.WriteBits(itemCounter, 20);
    data.WriteGuidMask(guid, 4, 7, 3);
    data.FlushBits();

    data.WriteGuidBytes(guid, 0, 2);
    data.WriteString(questTitle);
    data.append(currencyData);
    data.append(itemData);
    data.WriteGuidBytes(guid, 3, 1);
    data.WriteString(requestItemsText);
    data.WriteGuidBytes(guid, 4, 5, 7, 6);

    _session->SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_QUESTGIVER_REQUEST_ITEMS NPCGuid=%u, questid=%u", GUID_LOPART(npcGuid), quest->GetQuestId());
}

void PlayerMenu::AddQuestLevelToTitle(std::string &title, int32 level)
{
    // Adds the quest level to the front of the quest title
    // example: [13] Westfall Stew

    std::stringstream questTitlePretty;
    questTitlePretty << "[" << level << "] " << title;
    title = questTitlePretty.str();
}
