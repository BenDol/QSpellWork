#ifndef SWFORM_H
#define SWFORM_H

#include <QtCore/QSettings>

#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QCompleter>
#include <QtGui/QIcon>

#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>

#include "SWObject.h"
#include "ui_SWMainUI.h"

class SWObject;
class SpellListSortedModel;

class SWMainForm : public QMainWindow, public Ui::SWMainUI
{
    Q_OBJECT

    public:
        SWMainForm(QWidget* parent = 0);
        ~SWMainForm();

        void saveSettings();
        void loadSettings();

        bool isRegExp() const { return m_regExp->isChecked(); }
        void setRegExp(bool enable) { m_regExp->setChecked(enable); }

        QWebView* getBrowser(quint8 num) const
        {
            switch (num)
            {
                case 1: return webView1;
                case 2: return webView2;
                case 3: return webView3;
                default: return webView1;
            }
        }

    signals:
        void signalSearch(quint8 type);

    private slots:
        void slotAbout();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSearch(quint8 type);
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotRegExp();
        void slotModeDatabase();
        void slotModeShow();
        void slotModeCompare();
        void slotPrevRow();
        void slotNextRow();

        void slotConnectToDatabase();
        void slotSpellTable();
        void slotAutoRelate();
        void slotResetRelate();

        bool event(QEvent* ev);

    private:
        void loadComboBoxes();
        void detectLocale();
        void createModeButton();
        void initializeCompleter();

        QSettings* m_settings;
        SpellListSortedModel* m_sortedModel;
        Ui::SWMainUI m_ui;
        SWObject* m_sw;
        QToolButton* m_modeButton;
        QAction* m_regExp;
        QAction* m_about;
        QAction* m_update;
};

class Enums : public QObject
{
    Q_OBJECT
public:

    enum LocalesDBC
    {
        enUS,
        koKR,
        frFR,
        deDE,
        zhCN,
        zhTW,
        esES,
        esMX,
        ruRU

    };

    enum Mechanic
    {
        MECHANIC_NONE               = 0,
        MECHANIC_CHARM              = 1,
        MECHANIC_DISORIENTED        = 2,
        MECHANIC_DISARM             = 3,
        MECHANIC_DISTRACT           = 4,
        MECHANIC_FEAR               = 5,
        MECHANIC_GRIP               = 6,

        MECHANIC_ROOT               = 7,
        MECHANIC_PACIFY             = 8,
        MECHANIC_SILENCE            = 9,
        MECHANIC_SLEEP              = 10,
        MECHANIC_SNARE              = 11,
        MECHANIC_STUN               = 12,
        MECHANIC_FREEZE             = 13,
        MECHANIC_KNOCKOUT           = 14,
        MECHANIC_BLEED              = 15,
        MECHANIC_BANDAGE            = 16,
        MECHANIC_POLYMORPH          = 17,
        MECHANIC_BANISH             = 18,
        MECHANIC_SHIELD             = 19,
        MECHANIC_SHACKLE            = 20,
        MECHANIC_MOUNT              = 21,
        MECHANIC_INFECTED           = 22,

        MECHANIC_TURN               = 23,
        MECHANIC_HORROR             = 24,
        MECHANIC_INVULNERABILITY    = 25,
        MECHANIC_INTERRUPT          = 26,
        MECHANIC_DAZE               = 27,
        MECHANIC_DISCOVERY          = 28,
        MECHANIC_IMMUNE_SHIELD      = 29,
        MECHANIC_SAPPED             = 30,
        MECHANIC_ENRAGED            = 31
    };

    enum PreventionType
    {
        SPELL_PREVENTION_TYPE_NONE      = 0,
        SPELL_PREVENTION_TYPE_SILENCE   = 1,
        SPELL_PREVENTION_TYPE_PACIFY    = 2
    };

    enum DamageClass
    {
        SPELL_DAMAGE_CLASS_NONE     = 0,
        SPELL_DAMAGE_CLASS_MAGIC    = 1,
        SPELL_DAMAGE_CLASS_MELEE    = 2,
        SPELL_DAMAGE_CLASS_RANGED   = 3
    };

    enum SpellSchools
    {
        SPELL_SCHOOL_PHYSICAL   = 0,
        SPELL_SCHOOL_HOLY       = 1,
        SPELL_SCHOOL_FIRE       = 2,
        SPELL_SCHOOL_NATURE     = 3,
        SPELL_SCHOOL_FROST      = 4,
        SPELL_SCHOOL_SHADOW     = 5,
        SPELL_SCHOOL_ARCANE     = 6




    };

    enum SpellSchoolMask

    {
        MASK_NONE      = 0x00,
        MASK_PHYSICAL  = (1 << SPELL_SCHOOL_PHYSICAL),

        MASK_HOLY      = (1 << SPELL_SCHOOL_HOLY),
        MASK_FIRE      = (1 << SPELL_SCHOOL_FIRE),
        MASK_NATURE    = (1 << SPELL_SCHOOL_NATURE),
        MASK_FROST     = (1 << SPELL_SCHOOL_FROST),
        MASK_SHADOW    = (1 << SPELL_SCHOOL_SHADOW),
        MASK_ARCANE    = (1 << SPELL_SCHOOL_ARCANE),

        // unions

        // 124, not include normal and holy damage
        MASK_SPELL     = (MASK_FIRE | MASK_NATURE | MASK_FROST | MASK_SHADOW | MASK_ARCANE),
        // 126
        MASK_MAGIC     = (MASK_HOLY | MASK_SPELL),
        // 127
        MASK_ALL       = (MASK_PHYSICAL | MASK_MAGIC)

    };

    enum Effects
    {
        NO_SPELL_EFFECT                         = 0,

        SPELL_EFFECT_INSTAKILL                  = 1,
        SPELL_EFFECT_SCHOOL_DAMAGE              = 2,
        SPELL_EFFECT_DUMMY                      = 3,
        SPELL_EFFECT_PORTAL_TELEPORT            = 4,
        SPELL_EFFECT_TELEPORT_UNITS             = 5,
        SPELL_EFFECT_APPLY_AURA                 = 6,
        SPELL_EFFECT_ENVIRONMENTAL_DAMAGE       = 7,
        SPELL_EFFECT_POWER_DRAIN                = 8,
        SPELL_EFFECT_HEALTH_LEECH               = 9,
        SPELL_EFFECT_HEAL                       = 10,
        SPELL_EFFECT_BIND                       = 11,
        SPELL_EFFECT_PORTAL                     = 12,
        SPELL_EFFECT_RITUAL_BASE                = 13,
        SPELL_EFFECT_RITUAL_SPECIALIZE          = 14,
        SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL     = 15,
        SPELL_EFFECT_QUEST_COMPLETE             = 16,
        SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL     = 17,
        SPELL_EFFECT_RESURRECT                  = 18,
        SPELL_EFFECT_ADD_EXTRA_ATTACKS          = 19,
        SPELL_EFFECT_DODGE                      = 20,
        SPELL_EFFECT_EVADE                      = 21,
        SPELL_EFFECT_PARRY                      = 22,
        SPELL_EFFECT_BLOCK                      = 23,
        SPELL_EFFECT_CREATE_ITEM                = 24,
        SPELL_EFFECT_WEAPON                     = 25,
        SPELL_EFFECT_DEFENSE                    = 26,
        SPELL_EFFECT_PERSISTENT_AREA_AURA       = 27,
        SPELL_EFFECT_SUMMON                     = 28,
        SPELL_EFFECT_LEAP                       = 29,
        SPELL_EFFECT_ENERGIZE                   = 30,
        SPELL_EFFECT_WEAPON_PERCENT_DAMAGE      = 31,
        SPELL_EFFECT_TRIGGER_MISSILE            = 32,
        SPELL_EFFECT_OPEN_LOCK                  = 33,
        SPELL_EFFECT_SUMMON_CHANGE_ITEM         = 34,
        SPELL_EFFECT_APPLY_AREA_AURA_PARTY      = 35,
        SPELL_EFFECT_LEARN_SPELL                = 36,
        SPELL_EFFECT_SPELL_DEFENSE              = 37,
        SPELL_EFFECT_DISPEL                     = 38,
        SPELL_EFFECT_LANGUAGE                   = 39,
        SPELL_EFFECT_DUAL_WIELD                 = 40,
        SPELL_EFFECT_JUMP                       = 41,
        SPELL_EFFECT_JUMP2                      = 42,
        SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER = 43,
        SPELL_EFFECT_SKILL_STEP                 = 44,
        SPELL_EFFECT_ADD_HONOR                  = 45,
        SPELL_EFFECT_SPAWN                      = 46,
        SPELL_EFFECT_TRADE_SKILL                = 47,
        SPELL_EFFECT_STEALTH                    = 48,
        SPELL_EFFECT_DETECT                     = 49,
        SPELL_EFFECT_TRANS_DOOR                 = 50,
        SPELL_EFFECT_FORCE_CRITICAL_HIT         = 51,
        SPELL_EFFECT_GUARANTEE_HIT              = 52,
        SPELL_EFFECT_ENCHANT_ITEM               = 53,
        SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY     = 54,
        SPELL_EFFECT_TAMECREATURE               = 55,
        SPELL_EFFECT_SUMMON_PET                 = 56,
        SPELL_EFFECT_LEARN_PET_SPELL            = 57,
        SPELL_EFFECT_WEAPON_DAMAGE              = 58,
        SPELL_EFFECT_CREATE_RANDOM_ITEM         = 59,
        SPELL_EFFECT_PROFICIENCY                = 60,
        SPELL_EFFECT_SEND_EVENT                 = 61,
        SPELL_EFFECT_POWER_BURN                 = 62,
        SPELL_EFFECT_THREAT                     = 63,
        SPELL_EFFECT_TRIGGER_SPELL              = 64,
        SPELL_EFFECT_APPLY_AREA_AURA_RAID       = 65,
        SPELL_EFFECT_CREATE_MANA_GEM            = 66,
        SPELL_EFFECT_HEAL_MAX_HEALTH            = 67,
        SPELL_EFFECT_INTERRUPT_CAST             = 68,
        SPELL_EFFECT_DISTRACT                   = 69,
        SPELL_EFFECT_PULL                       = 70,
        SPELL_EFFECT_PICKPOCKET                 = 71,
        SPELL_EFFECT_ADD_FARSIGHT               = 72,
        SPELL_EFFECT_UNTRAIN_TALENTS            = 73,
        SPELL_EFFECT_APPLY_GLYPH                = 74,
        SPELL_EFFECT_HEAL_MECHANICAL            = 75,
        SPELL_EFFECT_SUMMON_OBJECT_WILD         = 76,
        SPELL_EFFECT_SCRIPT_EFFECT              = 77,
        SPELL_EFFECT_ATTACK                     = 78,
        SPELL_EFFECT_SANCTUARY                  = 79,
        SPELL_EFFECT_ADD_COMBO_POINTS           = 80,
        SPELL_EFFECT_CREATE_HOUSE               = 81,
        SPELL_EFFECT_BIND_SIGHT                 = 82,
        SPELL_EFFECT_DUEL                       = 83,
        SPELL_EFFECT_STUCK                      = 84,
        SPELL_EFFECT_SUMMON_PLAYER              = 85,
        SPELL_EFFECT_ACTIVATE_OBJECT            = 86,
        SPELL_EFFECT_WMO_DAMAGE                 = 87,
        SPELL_EFFECT_WMO_REPAIR                 = 88,
        SPELL_EFFECT_WMO_CHANGE                 = 89,
        SPELL_EFFECT_KILL_CREDIT                = 90,
        SPELL_EFFECT_THREAT_ALL                 = 91,
        SPELL_EFFECT_ENCHANT_HELD_ITEM          = 92,
        SPELL_EFFECT_BREAK_PLAYER_TARGETING     = 93,
        SPELL_EFFECT_SELF_RESURRECT             = 94,
        SPELL_EFFECT_SKINNING                   = 95,
        SPELL_EFFECT_CHARGE                     = 96,
        SPELL_EFFECT_SUMMON_ALL_TOTEMS          = 97,
        SPELL_EFFECT_KNOCK_BACK                 = 98,
        SPELL_EFFECT_DISENCHANT                 = 99,
        SPELL_EFFECT_INEBRIATE                  = 100,
        SPELL_EFFECT_FEED_PET                   = 101,
        SPELL_EFFECT_DISMISS_PET                = 102,
        SPELL_EFFECT_REPUTATION                 = 103,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT1        = 104,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT2        = 105,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT3        = 106,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT4        = 107,
        SPELL_EFFECT_DISPEL_MECHANIC            = 108,
        SPELL_EFFECT_SUMMON_DEAD_PET            = 109,
        SPELL_EFFECT_DESTROY_ALL_TOTEMS         = 110,
        SPELL_EFFECT_DURABILITY_DAMAGE          = 111,
        SPELL_EFFECT_112                        = 112,
        SPELL_EFFECT_RESURRECT_NEW              = 113,
        SPELL_EFFECT_ATTACK_ME                  = 114,
        SPELL_EFFECT_DURABILITY_DAMAGE_PCT      = 115,
        SPELL_EFFECT_SKIN_PLAYER_CORPSE         = 116,
        SPELL_EFFECT_SPIRIT_HEAL                = 117,
        SPELL_EFFECT_SKILL                      = 118,
        SPELL_EFFECT_APPLY_AREA_AURA_PET        = 119,
        SPELL_EFFECT_TELEPORT_GRAVEYARD         = 120,
        SPELL_EFFECT_NORMALIZED_WEAPON_DMG      = 121,
        SPELL_EFFECT_122                        = 122,
        SPELL_EFFECT_SEND_TAXI                  = 123,
        SPELL_EFFECT_PLAYER_PULL                = 124,
        SPELL_EFFECT_MODIFY_THREAT_PERCENT      = 125,
        SPELL_EFFECT_STEAL_BENEFICIAL_BUFF      = 126,
        SPELL_EFFECT_PROSPECTING                = 127,
        SPELL_EFFECT_APPLY_AREA_AURA_FRIEND     = 128,
        SPELL_EFFECT_APPLY_AREA_AURA_ENEMY      = 129,
        SPELL_EFFECT_REDIRECT_THREAT            = 130,
        SPELL_EFFECT_131                        = 131,
        SPELL_EFFECT_PLAY_MUSIC                 = 132,
        SPELL_EFFECT_UNLEARN_SPECIALIZATION     = 133,
        SPELL_EFFECT_KILL_CREDIT2               = 134,
        SPELL_EFFECT_CALL_PET                   = 135,
        SPELL_EFFECT_HEAL_PCT                   = 136,
        SPELL_EFFECT_ENERGIZE_PCT               = 137,
        SPELL_EFFECT_LEAP_BACK                  = 138,
        SPELL_EFFECT_CLEAR_QUEST                = 139,
        SPELL_EFFECT_FORCE_CAST                 = 140,
        SPELL_EFFECT_141                        = 141,
        SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE   = 142,
        SPELL_EFFECT_APPLY_AREA_AURA_OWNER      = 143,
        SPELL_EFFECT_144                        = 144,
        SPELL_EFFECT_145                        = 145,
        SPELL_EFFECT_ACTIVATE_RUNE              = 146,
        SPELL_EFFECT_QUEST_FAIL                 = 147,
        SPELL_EFFECT_148                        = 148,
        SPELL_EFFECT_149                        = 149,
        SPELL_EFFECT_150                        = 150,
        SPELL_EFFECT_TRIGGER_SPELL_2            = 151,
        SPELL_EFFECT_152                        = 152,
        SPELL_EFFECT_153                        = 153,
        SPELL_EFFECT_154                        = 154,
        SPELL_EFFECT_TITAN_GRIP                 = 155,
        SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC     = 156,
        SPELL_EFFECT_CREATE_ITEM_2              = 157,
        SPELL_EFFECT_MILLING                    = 158,
        SPELL_EFFECT_ALLOW_RENAME_PET           = 159,
        SPELL_EFFECT_160                        = 160,
        SPELL_EFFECT_TALENT_SPEC_COUNT          = 161,
        SPELL_EFFECT_TALENT_SPEC_SELECT         = 162,
        SPELL_EFFECT_163                        = 163,
        SPELL_EFFECT_CANCEL_AURA                = 164
    };

    enum TargetFlags
    {
        TARGET_FLAG_SELF            = 0x00,
        TARGET_FLAG_UNUSED1         = 1 << 0x00,
        TARGET_FLAG_UNIT            = 1 << 0x01,
        TARGET_FLAG_UNUSED2         = 1 << 0x02,
        TARGET_FLAG_UNUSED3         = 1 << 0x03,
        TARGET_FLAG_ITEM            = 1 << 0x04,
        TARGET_FLAG_SOURCE_LOCATION = 1 << 0x05,
        TARGET_FLAG_DEST_LOCATION   = 1 << 0x06,
        TARGET_FLAG_OBJECT_UNK      = 1 << 0x07,
        TARGET_FLAG_UNIT_UNK        = 1 << 0x08,
        TARGET_FLAG_PVP_CORPSE      = 1 << 0x09,
        TARGET_FLAG_UNIT_CORPSE     = 1 << 0x0A,
        TARGET_FLAG_OBJECT          = 1 << 0x0B,
        TARGET_FLAG_TRADE_ITEM      = 1 << 0x0C,
        TARGET_FLAG_STRING          = 1 << 0x0D,
        TARGET_FLAG_UNK1            = 1 << 0x0E,
        TARGET_FLAG_CORPSE          = 1 << 0x0F,
        TARGET_FLAG_UNK2            = 1 << 0x10,
        TARGET_FLAG_GLYPH           = 1 << 0x11,
        TARGET_FLAG_UNK3            = 1 << 0x12,
        TARGET_FLAG_UNK4            = 1 << 0x13
    };

    enum CreatureTypeMask
    {
        NONE            = 0x0,
        BEAST           = 1 << 0x0,
        DRAGONKIN       = 1 << 0x1,
        DEMON           = 1 << 0x2,
        ELEMENTAL       = 1 << 0x3,
        GIANT           = 1 << 0x4,
        UNDEAD          = 1 << 0x5,
        HUMANOID        = 1 << 0x6,
        CRITTER         = 1 << 0x7,
        MECHANICAL      = 1 << 0x8,
        NOT_SPECIFIED   = 1 << 0x9,
        TOTEM_CREATURE  = 1 << 0xA,
        NON_COMBAT_PET  = 1 << 0xB,
        GAS_CLOUD       = 1 << 0xC
    };

    enum Attributes
    {
        SPELL_ATTR_UNK0                             = 1 << 0x00,
        SPELL_ATTR_RANGED                           = 1 << 0x01,
        SPELL_ATTR_ON_NEXT_SWING_1                  = 1 << 0x02,
        SPELL_ATTR_UNK3                             = 1 << 0x03,
        SPELL_ATTR_UNK4                             = 1 << 0x04,
        SPELL_ATTR_TRADESPELL                       = 1 << 0x05,
        SPELL_ATTR_PASSIVE                          = 1 << 0x06,
        SPELL_ATTR_UNK7                             = 1 << 0x07,
        SPELL_ATTR_UNK8                             = 1 << 0x08,
        SPELL_ATTR_UNK9                             = 1 << 0x09,
        SPELL_ATTR_ON_NEXT_SWING_2                  = 1 << 0x0A,
        SPELL_ATTR_UNK11                            = 1 << 0x0B,
        SPELL_ATTR_DAYTIME_ONLY                     = 1 << 0x0C,
        SPELL_ATTR_NIGHT_ONLY                       = 1 << 0x0D,
        SPELL_ATTR_INDOORS_ONLY                     = 1 << 0x0E,
        SPELL_ATTR_OUTDOORS_ONLY                    = 1 << 0x0F,
        SPELL_ATTR_NOT_SHAPESHIFT                   = 1 << 0x10,
        SPELL_ATTR_ONLY_STEALTHED                   = 1 << 0x11,
        SPELL_ATTR_UNK18                            = 1 << 0x12,
        SPELL_ATTR_LEVEL_DAMAGE_CALCULATION         = 1 << 0x13,
        SPELL_ATTR_STOP_ATTACK_TARGET               = 1 << 0x14,
        SPELL_ATTR_IMPOSSIBLE_DODGE_PARRY_BLOCK     = 1 << 0x15,
        SPELL_ATTR_UNK22                            = 1 << 0x16,
        SPELL_ATTR_UNK23                            = 1 << 0x17,
        SPELL_ATTR_CASTABLE_WHILE_MOUNTED           = 1 << 0x18,
        SPELL_ATTR_DISABLED_WHILE_ACTIVE            = 1 << 0x19,
        SPELL_ATTR_UNK26                            = 1 << 0x1A,
        SPELL_ATTR_CASTABLE_WHILE_SITTING           = 1 << 0x1B,
        SPELL_ATTR_CANT_USED_IN_COMBAT              = 1 << 0x1C,
        SPELL_ATTR_UNAFFECTED_BY_INVULNERABILITY    = 1 << 0x1D,
        SPELL_ATTR_UNK30                            = 1 << 0x1E,
        SPELL_ATTR_CANT_CANCEL                      = 1 << 0x1F
    };

    enum AttributesEx
    {
        SPELL_ATTR_EX_UNK0                          = 1 << 0x00,
        SPELL_ATTR_EX_DRAIN_ALL_POWER               = 1 << 0x01,
        SPELL_ATTR_EX_CHANNELED_1                   = 1 << 0x02,
        SPELL_ATTR_EX_UNK3                          = 1 << 0x03,
        SPELL_ATTR_EX_UNK4                          = 1 << 0x04,
        SPELL_ATTR_EX_NOT_BREAK_STEALTH             = 1 << 0x05,
        SPELL_ATTR_EX_CHANNELED_2                   = 1 << 0x06,
        SPELL_ATTR_EX_NEGATIVE                      = 1 << 0x07,
        SPELL_ATTR_EX_NOT_IN_COMBAT_TARGET          = 1 << 0x08,
        SPELL_ATTR_EX_UNK9                          = 1 << 0x09,
        SPELL_ATTR_EX_NO_INITIAL_AGGRO              = 1 << 0x0A,
        SPELL_ATTR_EX_UNK11                         = 1 << 0x0B,
        SPELL_ATTR_EX_UNK12                         = 1 << 0x0C,
        SPELL_ATTR_EX_UNK13                         = 1 << 0x0D,
        SPELL_ATTR_EX_UNK14                         = 1 << 0x0E,
        SPELL_ATTR_EX_DISPEL_AURAS_ON_IMMUNITY      = 1 << 0x0F,
        SPELL_ATTR_EX_UNAFFECTED_BY_SCHOOL_IMMUNE   = 1 << 0x10,
        SPELL_ATTR_EX_UNK17                         = 1 << 0x11,
        SPELL_ATTR_EX_UNK18                         = 1 << 0x12,
        SPELL_ATTR_EX_UNK19                         = 1 << 0x13,
        SPELL_ATTR_EX_REQ_TARGET_COMBO_POINTS       = 1 << 0x14,
        SPELL_ATTR_EX_UNK21                         = 1 << 0x15,
        SPELL_ATTR_EX_REQ_COMBO_POINTS              = 1 << 0x16,
        SPELL_ATTR_EX_UNK23                         = 1 << 0x17,
        SPELL_ATTR_EX_UNK24                         = 1 << 0x18,
        SPELL_ATTR_EX_UNK25                         = 1 << 0x19,
        SPELL_ATTR_EX_UNK26                         = 1 << 0x1A,
        SPELL_ATTR_EX_UNK27                         = 1 << 0x1B,
        SPELL_ATTR_EX_UNK28                         = 1 << 0x1C,
        SPELL_ATTR_EX_UNK29                         = 1 << 0x1D,
        SPELL_ATTR_EX_UNK30                         = 1 << 0x1E,
        SPELL_ATTR_EX_UNK31                         = 1 << 0x1F
    };

    enum AttributesEx2
    {
        SPELL_ATTR_EX2_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX2_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX2_CANT_REFLECTED               = 1 << 0x02,
        SPELL_ATTR_EX2_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX2_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX2_AUTOREPEAT_FLAG              = 1 << 0x05,
        SPELL_ATTR_EX2_UNK6                         = 1 << 0x06,
        SPELL_ATTR_EX2_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX2_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX2_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX2_UNK10                        = 1 << 0x0A,
        SPELL_ATTR_EX2_HEALTH_FUNNEL                = 1 << 0x0B,
        SPELL_ATTR_EX2_UNK12                        = 1 << 0x0C,
        SPELL_ATTR_EX2_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX2_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX2_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX2_UNK16                        = 1 << 0x10,
        SPELL_ATTR_EX2_UNK17                        = 1 << 0x11,
        SPELL_ATTR_EX2_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX2_NOT_NEED_SHAPESHIFT          = 1 << 0x13,
        SPELL_ATTR_EX2_UNK20                        = 1 << 0x14,
        SPELL_ATTR_EX2_DAMAGE_REDUCED_SHIELD        = 1 << 0x15,
        SPELL_ATTR_EX2_UNK22                        = 1 << 0x16,
        SPELL_ATTR_EX2_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX2_UNK24                        = 1 << 0x18,
        SPELL_ATTR_EX2_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX2_UNK26                        = 1 << 0x1A,
        SPELL_ATTR_EX2_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX2_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX2_CANT_CRIT                    = 1 << 0x1D,
        SPELL_ATTR_EX2_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX2_FOOD_BUFF                    = 1 << 0x1F
    };

    enum AttributesEx3
    {
        SPELL_ATTR_EX3_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX3_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX3_UNK2                         = 1 << 0x02,
        SPELL_ATTR_EX3_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX3_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX3_UNK5                         = 1 << 0x05,
        SPELL_ATTR_EX3_UNK6                         = 1 << 0x06,
        SPELL_ATTR_EX3_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX3_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX3_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX3_MAIN_HAND                    = 1 << 0x0A,
        SPELL_ATTR_EX3_BATTLEGROUND                 = 1 << 0x0B,
        SPELL_ATTR_EX3_CAST_ON_DEAD                 = 1 << 0x0C,
        SPELL_ATTR_EX3_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX3_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX3_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX3_UNK16                        = 1 << 0x10,
        SPELL_ATTR_EX3_UNK17                        = 1 << 0x11,
        SPELL_ATTR_EX3_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX3_UNK19                        = 1 << 0x13,
        SPELL_ATTR_EX3_DEATH_PERSISTENT             = 1 << 0x14,
        SPELL_ATTR_EX3_UNK21                        = 1 << 0x15,
        SPELL_ATTR_EX3_REQ_WAND                     = 1 << 0x16,
        SPELL_ATTR_EX3_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX3_REQ_OFFHAND                  = 1 << 0x18,
        SPELL_ATTR_EX3_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX3_UNK26                        = 1 << 0x1A,
        SPELL_ATTR_EX3_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX3_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX3_UNK29                        = 1 << 0x1D,
        SPELL_ATTR_EX3_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX3_UNK31                        = 1 << 0x1F
    };

    enum AttributesEx4
    {
        SPELL_ATTR_EX4_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX4_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX4_UNK2                         = 1 << 0x02,
        SPELL_ATTR_EX4_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX4_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX4_UNK5                         = 1 << 0x05,
        SPELL_ATTR_EX4_NOT_STEALABLE                = 1 << 0x06,
        SPELL_ATTR_EX4_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX4_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX4_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX4_SPELL_VS_EXTEND_COST         = 1 << 0x0A,
        SPELL_ATTR_EX4_UNK11                        = 1 << 0x0B,
        SPELL_ATTR_EX4_UNK12                        = 1 << 0x0C,
        SPELL_ATTR_EX4_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX4_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX4_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX4_NOT_USABLE_IN_ARENA          = 1 << 0x10,
        SPELL_ATTR_EX4_USABLE_IN_ARENA              = 1 << 0x11,
        SPELL_ATTR_EX4_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX4_UNK19                        = 1 << 0x13,
        SPELL_ATTR_EX4_UNK20                        = 1 << 0x14,
        SPELL_ATTR_EX4_UNK21                        = 1 << 0x15,
        SPELL_ATTR_EX4_UNK22                        = 1 << 0x16,
        SPELL_ATTR_EX4_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX4_UNK24                        = 1 << 0x18,
        SPELL_ATTR_EX4_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX4_CAST_ONLY_IN_OUTLAND         = 1 << 0x1A,
        SPELL_ATTR_EX4_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX4_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX4_UNK29                        = 1 << 0x1D,
        SPELL_ATTR_EX4_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX4_UNK31                        = 1 << 0x1F
    };

    enum AttributesEx5
    {
        SPELL_ATTR_EX5_UNK0                       = 1 << 0x00,
        SPELL_ATTR_EX5_NO_REAGENT_WHILE_PREP      = 1 << 0x01,
        SPELL_ATTR_EX5_UNK2                       = 1 << 0x02,
        SPELL_ATTR_EX5_USABLE_WHILE_STUNNED       = 1 << 0x03,
        SPELL_ATTR_EX5_UNK4                       = 1 << 0x04,
        SPELL_ATTR_EX5_SINGLE_TARGET_SPELL        = 1 << 0x05,
        SPELL_ATTR_EX5_UNK6                       = 1 << 0x06,
        SPELL_ATTR_EX5_UNK7                       = 1 << 0x07,
        SPELL_ATTR_EX5_UNK8                       = 1 << 0x08,
        SPELL_ATTR_EX5_START_PERIODIC_AT_APPLY    = 1 << 0x09,
        SPELL_ATTR_EX5_UNK10                      = 1 << 0x0A,
        SPELL_ATTR_EX5_UNK11                      = 1 << 0x0B,
        SPELL_ATTR_EX5_UNK12                      = 1 << 0x0C,
        SPELL_ATTR_EX5_UNK13                      = 1 << 0x0D,
        SPELL_ATTR_EX5_UNK14                      = 1 << 0x0E,
        SPELL_ATTR_EX5_UNK15                      = 1 << 0x0F,
        SPELL_ATTR_EX5_UNK16                      = 1 << 0x10,
        SPELL_ATTR_EX5_USABLE_WHILE_FEARED        = 1 << 0x11,
        SPELL_ATTR_EX5_USABLE_WHILE_CONFUSED      = 1 << 0x12,
        SPELL_ATTR_EX5_UNK19                      = 1 << 0x13,
        SPELL_ATTR_EX5_UNK20                      = 1 << 0x14,
        SPELL_ATTR_EX5_UNK21                      = 1 << 0x15,
        SPELL_ATTR_EX5_UNK22                      = 1 << 0x16,
        SPELL_ATTR_EX5_UNK23                      = 1 << 0x17,
        SPELL_ATTR_EX5_UNK24                      = 1 << 0x18,
        SPELL_ATTR_EX5_UNK25                      = 1 << 0x19,
        SPELL_ATTR_EX5_UNK26                      = 1 << 0x1A,
        SPELL_ATTR_EX5_UNK27                      = 1 << 0x1B,
        SPELL_ATTR_EX5_UNK28                      = 1 << 0x1C,
        SPELL_ATTR_EX5_UNK29                      = 1 << 0x1D,
        SPELL_ATTR_EX5_UNK30                      = 1 << 0x1E,
        SPELL_ATTR_EX5_UNK31                      = 1 << 0x1F
    };

    enum AttributesEx6
    {
        SPELL_ATTR_EX6_UNK0                       = 1 << 0x00,
        SPELL_ATTR_EX6_ONLY_IN_ARENA              = 1 << 0x01,
        SPELL_ATTR_EX6_UNK2                       = 1 << 0x02,
        SPELL_ATTR_EX6_UNK3                       = 1 << 0x03,
        SPELL_ATTR_EX6_UNK4                       = 1 << 0x04,
        SPELL_ATTR_EX6_UNK5                       = 1 << 0x05,
        SPELL_ATTR_EX6_UNK6                       = 1 << 0x06,
        SPELL_ATTR_EX6_UNK7                       = 1 << 0x07,
        SPELL_ATTR_EX6_UNK8                       = 1 << 0x08,
        SPELL_ATTR_EX6_UNK9                       = 1 << 0x09,
        SPELL_ATTR_EX6_UNK10                      = 1 << 0x0A,
        SPELL_ATTR_EX6_NOT_IN_RAID_INSTANCE       = 1 << 0x0B,
        SPELL_ATTR_EX6_UNK12                      = 1 << 0x0C,
        SPELL_ATTR_EX6_UNK13                      = 1 << 0x0D,
        SPELL_ATTR_EX6_UNK14                      = 1 << 0x0E,
        SPELL_ATTR_EX6_UNK15                      = 1 << 0x0F,
        SPELL_ATTR_EX6_UNK16                      = 1 << 0x10,
        SPELL_ATTR_EX6_UNK17                      = 1 << 0x11,
        SPELL_ATTR_EX6_UNK18                      = 1 << 0x12,
        SPELL_ATTR_EX6_UNK19                      = 1 << 0x13,
        SPELL_ATTR_EX6_UNK20                      = 1 << 0x14,
        SPELL_ATTR_EX6_UNK21                      = 1 << 0x15,
        SPELL_ATTR_EX6_UNK22                      = 1 << 0x16,
        SPELL_ATTR_EX6_UNK23                      = 1 << 0x17,
        SPELL_ATTR_EX6_UNK24                      = 1 << 0x18,
        SPELL_ATTR_EX6_UNK25                      = 1 << 0x19,
        SPELL_ATTR_EX6_UNK26                      = 1 << 0x1A,
        SPELL_ATTR_EX6_UNK27                      = 1 << 0x1B,
        SPELL_ATTR_EX6_UNK28                      = 1 << 0x1C,
        SPELL_ATTR_EX6_NO_DMG_PERCENT_MODS        = 1 << 0x1D,
        SPELL_ATTR_EX6_UNK30                      = 1 << 0x1E,
        SPELL_ATTR_EX6_UNK31                      = 1 << 0x1F
    };
    
    enum AttributesEx7
    {
        SPELL_ATTR_EX7_UNK0                       = 1 << 0x00,
        SPELL_ATTR_EX7_UNK1                       = 1 << 0x01,
        SPELL_ATTR_EX7_REACTIVATE_AT_RESURRECT    = 1 << 0x02,
        SPELL_ATTR_EX7_DISABLED_CLIENT_SIDE       = 1 << 0x03,
        SPELL_ATTR_EX7_UNK4                       = 1 << 0x04,
        SPELL_ATTR_EX7_SUMMON_PLAYER_TOTEM        = 1 << 0x05,
        SPELL_ATTR_EX7_UNK6                       = 1 << 0x06,
        SPELL_ATTR_EX7_UNK7                       = 1 << 0x07,
        SPELL_ATTR_EX7_HORDE_ONLY                 = 1 << 0x08,
        SPELL_ATTR_EX7_ALLIANCE_ONLY              = 1 << 0x09,
        SPELL_ATTR_EX7_DISPEL_CHARGES             = 1 << 0x0A,
        SPELL_ATTR_EX7_INTERRUPT_ONLY_NONPLAYER   = 1 << 0x0B,
        SPELL_ATTR_EX7_UNK12                      = 1 << 0x0C,
        SPELL_ATTR_EX7_UNK13                      = 1 << 0x0D,
        SPELL_ATTR_EX7_UNK14                      = 1 << 0x0E,
        SPELL_ATTR_EX7_UNK15                      = 1 << 0x0F,
        SPELL_ATTR_EX7_UNK16                      = 1 << 0x10,
        SPELL_ATTR_EX7_UNK17                      = 1 << 0x11,
        SPELL_ATTR_EX7_HAS_CHARGE_EFFECT          = 1 << 0x12,
        SPELL_ATTR_EX7_ZONE_TELEPORT              = 1 << 0x13,
        SPELL_ATTR_EX7_UNK20                      = 1 << 0x14,
        SPELL_ATTR_EX7_UNK21                      = 1 << 0x15,
        SPELL_ATTR_EX7_UNK22                      = 1 << 0x16,
        SPELL_ATTR_EX7_UNK23                      = 1 << 0x17,
        SPELL_ATTR_EX7_UNK24                      = 1 << 0x18,
        SPELL_ATTR_EX7_UNK25                      = 1 << 0x19,
        SPELL_ATTR_EX7_UNK26                      = 1 << 0x1A,
        SPELL_ATTR_EX7_UNK27                      = 1 << 0x1B,
        SPELL_ATTR_EX7_UNK28                      = 1 << 0x1C,
        SPELL_ATTR_EX7_UNK29                      = 1 << 0x1D,
        SPELL_ATTR_EX7_UNK30                      = 1 << 0x1E,
        SPELL_ATTR_EX7_UNK31                      = 1 << 0x1F
    };

    enum AuraType
    {
        SPELL_AURA_NONE                                     = 0,
        SPELL_AURA_BIND_SIGHT                               = 1,
        SPELL_AURA_MOD_POSSESS                              = 2,
        SPELL_AURA_PERIODIC_DAMAGE                          = 3,
        SPELL_AURA_DUMMY                                    = 4,
        SPELL_AURA_MOD_CONFUSE                              = 5,
        SPELL_AURA_MOD_CHARM                                = 6,
        SPELL_AURA_MOD_FEAR                                 = 7,
        SPELL_AURA_PERIODIC_HEAL                            = 8,
        SPELL_AURA_MOD_ATTACKSPEED                          = 9,
        SPELL_AURA_MOD_THREAT                               = 10,
        SPELL_AURA_MOD_TAUNT                                = 11,
        SPELL_AURA_MOD_STUN                                 = 12,
        SPELL_AURA_MOD_DAMAGE_DONE                          = 13,
        SPELL_AURA_MOD_DAMAGE_TAKEN                         = 14,
        SPELL_AURA_DAMAGE_SHIELD                            = 15,
        SPELL_AURA_MOD_STEALTH                              = 16,
        SPELL_AURA_MOD_STEALTH_DETECT                       = 17,
        SPELL_AURA_MOD_INVISIBILITY                         = 18,
        SPELL_AURA_MOD_INVISIBILITY_DETECTION               = 19,
        SPELL_AURA_OBS_MOD_HEALTH                           = 20,
        SPELL_AURA_OBS_MOD_MANA                             = 21,
        SPELL_AURA_MOD_RESISTANCE                           = 22,
        SPELL_AURA_PERIODIC_TRIGGER_SPELL                   = 23,
        SPELL_AURA_PERIODIC_ENERGIZE                        = 24,
        SPELL_AURA_MOD_PACIFY                               = 25,
        SPELL_AURA_MOD_ROOT                                 = 26,
        SPELL_AURA_MOD_SILENCE                              = 27,
        SPELL_AURA_REFLECT_SPELLS                           = 28,
        SPELL_AURA_MOD_STAT                                 = 29,
        SPELL_AURA_MOD_SKILL                                = 30,
        SPELL_AURA_MOD_INCREASE_SPEED                       = 31,
        SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED               = 32,
        SPELL_AURA_MOD_DECREASE_SPEED                       = 33,
        SPELL_AURA_MOD_INCREASE_HEALTH                      = 34,
        SPELL_AURA_MOD_INCREASE_ENERGY                      = 35,
        SPELL_AURA_MOD_SHAPESHIFT                           = 36,
        SPELL_AURA_EFFECT_IMMUNITY                          = 37,
        SPELL_AURA_STATE_IMMUNITY                           = 38,
        SPELL_AURA_SCHOOL_IMMUNITY                          = 39,
        SPELL_AURA_DAMAGE_IMMUNITY                          = 40,
        SPELL_AURA_DISPEL_IMMUNITY                          = 41,
        SPELL_AURA_PROC_TRIGGER_SPELL                       = 42,
        SPELL_AURA_PROC_TRIGGER_DAMAGE                      = 43,
        SPELL_AURA_TRACK_CREATURES                          = 44,
        SPELL_AURA_TRACK_RESOURCES                          = 45,
        SPELL_AURA_46                                       = 46,
        SPELL_AURA_MOD_PARRY_PERCENT                        = 47,
        SPELL_AURA_48                                       = 48,
        SPELL_AURA_MOD_DODGE_PERCENT                        = 49,
        SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT              = 50,
        SPELL_AURA_MOD_BLOCK_PERCENT                        = 51,
        SPELL_AURA_MOD_CRIT_PERCENT                         = 52,
        SPELL_AURA_PERIODIC_LEECH                           = 53,
        SPELL_AURA_MOD_HIT_CHANCE                           = 54,
        SPELL_AURA_MOD_SPELL_HIT_CHANCE                     = 55,
        SPELL_AURA_TRANSFORM                                = 56,
        SPELL_AURA_MOD_SPELL_CRIT_CHANCE                    = 57,
        SPELL_AURA_MOD_INCREASE_SWIM_SPEED                  = 58,
        SPELL_AURA_MOD_DAMAGE_DONE_CREATURE                 = 59,
        SPELL_AURA_MOD_PACIFY_SILENCE                       = 60,
        SPELL_AURA_MOD_SCALE                                = 61,
        SPELL_AURA_PERIODIC_HEALTH_FUNNEL                   = 62,
        SPELL_AURA_63                                       = 63,
        SPELL_AURA_PERIODIC_MANA_LEECH                      = 64,
        SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK              = 65,
        SPELL_AURA_FEIGN_DEATH                              = 66,
        SPELL_AURA_MOD_DISARM                               = 67,
        SPELL_AURA_MOD_STALKED                              = 68,
        SPELL_AURA_SCHOOL_ABSORB                            = 69,
        SPELL_AURA_EXTRA_ATTACKS                            = 70,
        SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL             = 71,
        SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT                = 72,
        SPELL_AURA_MOD_POWER_COST_SCHOOL                    = 73,
        SPELL_AURA_REFLECT_SPELLS_SCHOOL                    = 74,
        SPELL_AURA_MOD_LANGUAGE                             = 75,
        SPELL_AURA_FAR_SIGHT                                = 76,
        SPELL_AURA_MECHANIC_IMMUNITY                        = 77,
        SPELL_AURA_MOUNTED                                  = 78,
        SPELL_AURA_MOD_DAMAGE_PERCENT_DONE                  = 79,
        SPELL_AURA_MOD_PERCENT_STAT                         = 80,
        SPELL_AURA_SPLIT_DAMAGE_PCT                         = 81,
        SPELL_AURA_WATER_BREATHING                          = 82,
        SPELL_AURA_MOD_BASE_RESISTANCE                      = 83,
        SPELL_AURA_MOD_REGEN                                = 84,
        SPELL_AURA_MOD_POWER_REGEN                          = 85,
        SPELL_AURA_CHANNEL_DEATH_ITEM                       = 86,
        SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN                 = 87,
        SPELL_AURA_MOD_HEALTH_REGEN_PERCENT                 = 88,
        SPELL_AURA_PERIODIC_DAMAGE_PERCENT                  = 89,
        SPELL_AURA_90                                       = 90,
        SPELL_AURA_MOD_DETECT_RANGE                         = 91,
        SPELL_AURA_PREVENTS_FLEEING                         = 92,
        SPELL_AURA_MOD_UNATTACKABLE                         = 93,
        SPELL_AURA_INTERRUPT_REGEN                          = 94,
        SPELL_AURA_GHOST                                    = 95,
        SPELL_AURA_SPELL_MAGNET                             = 96,
        SPELL_AURA_MANA_SHIELD                              = 97,
        SPELL_AURA_MOD_SKILL_TALENT                         = 98,
        SPELL_AURA_MOD_ATTACK_POWER                         = 99,
        SPELL_AURA_AURAS_VISIBLE                            = 100,
        SPELL_AURA_MOD_RESISTANCE_PCT                       = 101,
        SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS            = 102,
        SPELL_AURA_MOD_TOTAL_THREAT                         = 103,
        SPELL_AURA_WATER_WALK                               = 104,
        SPELL_AURA_FEATHER_FALL                             = 105,
        SPELL_AURA_HOVER                                    = 106,
        SPELL_AURA_ADD_FLAT_MODIFIER                        = 107,
        SPELL_AURA_ADD_PCT_MODIFIER                         = 108,
        SPELL_AURA_ADD_TARGET_TRIGGER                       = 109,
        SPELL_AURA_MOD_POWER_REGEN_PERCENT                  = 110,
        SPELL_AURA_ADD_CASTER_HIT_TRIGGER                   = 111,
        SPELL_AURA_OVERRIDE_CLASS_SCRIPTS                   = 112,
        SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN                  = 113,
        SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT              = 114,
        SPELL_AURA_MOD_HEALING                              = 115,
        SPELL_AURA_MOD_REGEN_DURING_COMBAT                  = 116,
        SPELL_AURA_MOD_MECHANIC_RESISTANCE                  = 117,
        SPELL_AURA_MOD_HEALING_PCT                          = 118,
        SPELL_AURA_119                                      = 119,
        SPELL_AURA_UNTRACKABLE                              = 120,
        SPELL_AURA_EMPATHY                                  = 121,
        SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT                   = 122,
        SPELL_AURA_MOD_TARGET_RESISTANCE                    = 123,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER                  = 124,
        SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN                   = 125,
        SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT               = 126,
        SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS       = 127,
        SPELL_AURA_MOD_POSSESS_PET                          = 128,
        SPELL_AURA_MOD_SPEED_ALWAYS                         = 129,
        SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS                 = 130,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS           = 131,
        SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT              = 132,
        SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT              = 133,
        SPELL_AURA_MOD_MANA_REGEN_INTERRUPT                 = 134,
        SPELL_AURA_MOD_HEALING_DONE                         = 135,
        SPELL_AURA_MOD_HEALING_DONE_PERCENT                 = 136,
        SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE                = 137,
        SPELL_AURA_MOD_HASTE                                = 138,
        SPELL_AURA_FORCE_REACTION                           = 139,
        SPELL_AURA_MOD_RANGED_HASTE                         = 140,
        SPELL_AURA_MOD_RANGED_AMMO_HASTE                    = 141,
        SPELL_AURA_MOD_BASE_RESISTANCE_PCT                  = 142,
        SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE                 = 143,
        SPELL_AURA_SAFE_FALL                                = 144,
        SPELL_AURA_MOD_PET_TALENT_POINTS                    = 145,
        SPELL_AURA_ALLOW_TAME_PET_TYPE                      = 146,
        SPELL_AURA_MECHANIC_IMMUNITY_MASK                   = 147,
        SPELL_AURA_RETAIN_COMBO_POINTS                      = 148,
        SPELL_AURA_REDUCE_PUSHBACK                          = 149,
        SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT                = 150,
        SPELL_AURA_TRACK_STEALTHED                          = 151,
        SPELL_AURA_MOD_DETECTED_RANGE                       = 152,
        SPELL_AURA_SPLIT_DAMAGE_FLAT                        = 153,
        SPELL_AURA_MOD_STEALTH_LEVEL                        = 154,
        SPELL_AURA_MOD_WATER_BREATHING                      = 155,
        SPELL_AURA_MOD_REPUTATION_GAIN                      = 156,
        SPELL_AURA_PET_DAMAGE_MULTI                         = 157,
        SPELL_AURA_MOD_SHIELD_BLOCKVALUE                    = 158,
        SPELL_AURA_NO_PVP_CREDIT                            = 159,
        SPELL_AURA_MOD_AOE_AVOIDANCE                        = 160,
        SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT               = 161,
        SPELL_AURA_POWER_BURN_MANA                          = 162,
        SPELL_AURA_MOD_CRIT_DAMAGE_BONUS                    = 163,
        SPELL_AURA_164                                      = 164,
        SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS        = 165,
        SPELL_AURA_MOD_ATTACK_POWER_PCT                     = 166,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT              = 167,
        SPELL_AURA_MOD_DAMAGE_DONE_VERSUS                   = 168,
        SPELL_AURA_MOD_CRIT_PERCENT_VERSUS                  = 169,
        SPELL_AURA_DETECT_AMORE                             = 170,
        SPELL_AURA_MOD_SPEED_NOT_STACK                      = 171,
        SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK              = 172,
        SPELL_AURA_173                                      = 173,
        SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT         = 174,
        SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT        = 175,
        SPELL_AURA_SPIRIT_OF_REDEMPTION                     = 176,
        SPELL_AURA_AOE_CHARM                                = 177,
        SPELL_AURA_MOD_DEBUFF_RESISTANCE                    = 178,
        SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE           = 179,
        SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS             = 180,
        SPELL_AURA_181                                      = 181,
        SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT           = 182,
        SPELL_AURA_MOD_CRITICAL_THREAT                      = 183,
        SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE            = 184,
        SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE           = 185,
        SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE            = 186,
        SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE           = 187,
        SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE          = 188,
        SPELL_AURA_MOD_RATING                               = 189,
        SPELL_AURA_MOD_FACTION_REPUTATION_GAIN              = 190,
        SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED                = 191,
        SPELL_AURA_HASTE_MELEE                              = 192,
        SPELL_AURA_MELEE_SLOW                               = 193,
        SPELL_AURA_MOD_IGNORE_ABSORB_SCHOOL                 = 194,
        SPELL_AURA_MOD_IGNORE_ABSORB_FOR_SPELL              = 195,
        SPELL_AURA_MOD_COOLDOWN                             = 196,
        SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE= 197,
        SPELL_AURA_198                                      = 198,
        SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT           = 199,
        SPELL_AURA_MOD_KILL_XP_PCT                          = 200,
        SPELL_AURA_FLY                                      = 201,
        SPELL_AURA_IGNORE_COMBAT_RESULT                     = 202,
        SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE           = 203,
        SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE          = 204,
        SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_DAMAGE           = 205,
        SPELL_AURA_MOD_SPEED_MOUNTED                        = 206,
        SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED                = 207,
        SPELL_AURA_MOD_SPEED_FLIGHT                         = 208,
        SPELL_AURA_MOD_FLIGHT_SPEED_ALWAYS                  = 209,
        SPELL_AURA_210                                      = 210,
        SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK               = 211,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT  = 212,
        SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT               = 213,
        SPELL_AURA_214                                      = 214,
        SPELL_AURA_ARENA_PREPARATION                        = 215,
        SPELL_AURA_HASTE_SPELLS                             = 216,
        SPELL_AURA_217                                      = 217,
        SPELL_AURA_HASTE_RANGED                             = 218,
        SPELL_AURA_MOD_MANA_REGEN_FROM_STAT                 = 219,
        SPELL_AURA_MOD_RATING_FROM_STAT                     = 220,
        SPELL_AURA_221                                      = 221,
        SPELL_AURA_222                                      = 222,
        SPELL_AURA_223                                      = 223,
        SPELL_AURA_224                                      = 224,
        SPELL_AURA_PRAYER_OF_MENDING                        = 225,
        SPELL_AURA_PERIODIC_DUMMY                           = 226,
        SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE        = 227,
        SPELL_AURA_DETECT_STEALTH                           = 228,
        SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE                 = 229,
        SPELL_AURA_230                                      = 230,
        SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE            = 231,
        SPELL_AURA_MECHANIC_DURATION_MOD                    = 232,
        SPELL_AURA_233                                      = 233,
        SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK          = 234,
        SPELL_AURA_MOD_DISPEL_RESIST                        = 235,
        SPELL_AURA_CONTROL_VEHICLE                          = 236,
        SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER         = 237,
        SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER        = 238,
        SPELL_AURA_MOD_SCALE_2                              = 239,
        SPELL_AURA_MOD_EXPERTISE                            = 240,
        SPELL_AURA_FORCE_MOVE_FORWARD                       = 241,
        SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING            = 242,
        SPELL_AURA_243                                      = 243,
        SPELL_AURA_COMPREHEND_LANGUAGE                      = 244,
        SPELL_AURA_MOD_DURATION_OF_MAGIC_EFFECTS            = 245,
        SPELL_AURA_MOD_DURATION_OF_EFFECTS_BY_DISPEL        = 246,
        SPELL_AURA_247                                      = 247,
        SPELL_AURA_MOD_COMBAT_RESULT_CHANCE                 = 248,
        SPELL_AURA_CONVERT_RUNE                             = 249,
        SPELL_AURA_MOD_INCREASE_HEALTH_2                    = 250,
        SPELL_AURA_MOD_ENEMY_DODGE                          = 251,
        SPELL_AURA_252                                      = 252,
        SPELL_AURA_MOD_BLOCK_CRIT_CHANCE                    = 253,
        SPELL_AURA_MOD_DISARM_SHIELD                        = 254,
        SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT        = 255,
        SPELL_AURA_NO_REAGENT_USE                           = 256,
        SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS         = 257,
        SPELL_AURA_258                                      = 258,
        SPELL_AURA_259                                      = 259,
        SPELL_AURA_SCREEN_EFFECT                            = 260,
        SPELL_AURA_PHASE                                    = 261,
        SPELL_AURA_IGNORE_UNIT_STATE                        = 262,
        SPELL_AURA_ALLOW_ONLY_ABILITY                       = 263,
        SPELL_AURA_264                                      = 264,
        SPELL_AURA_265                                      = 265,
        SPELL_AURA_266                                      = 266,
        SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL             = 267,
        SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT         = 268,
        SPELL_AURA_MOD_IGNORE_DAMAGE_REDUCTION_SCHOOL       = 269,
        SPELL_AURA_MOD_IGNORE_TARGET_RESIST                 = 270,
        SPELL_AURA_MOD_DAMAGE_FROM_CASTER                   = 271,
        SPELL_AURA_MAELSTROM_WEAPON                         = 272,
        SPELL_AURA_X_RAY                                    = 273,
        SPELL_AURA_274                                      = 274,
        SPELL_AURA_MOD_IGNORE_SHAPESHIFT                    = 275,
        SPELL_AURA_276                                      = 276,
        SPELL_AURA_MOD_MAX_AFFECTED_TARGETS                 = 277,
        SPELL_AURA_MOD_DISARM_RANGED                        = 278,
        SPELL_AURA_279                                      = 279,
        SPELL_AURA_MOD_TARGET_ARMOR_PCT                     = 280,
        SPELL_AURA_MOD_HONOR_GAIN                           = 281,
        SPELL_AURA_MOD_BASE_HEALTH_PCT                      = 282,
        SPELL_AURA_MOD_HEALING_RECEIVED                     = 283,
        SPELL_AURA_284                                      = 284,
        SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR                = 285,
        SPELL_AURA_ABILITY_PERIODIC_CRIT                    = 286,
        SPELL_AURA_DEFLECT_SPELLS                           = 287,
        SPELL_AURA_MOD_PARRY_FROM_BEHIND_PERCENT            = 288,
        SPELL_AURA_289                                      = 289,
        SPELL_AURA_MOD_ALL_CRIT_CHANCE                      = 290,
        SPELL_AURA_MOD_QUEST_XP_PCT                         = 291,
        SPELL_AURA_OPEN_STABLE                              = 292,
        SPELL_AURA_ADD_MECHANIC_ABILITIES                   = 293,
        SPELL_AURA_STOP_NATURAL_MANA_REGEN                  = 294,
        SPELL_AURA_295                                      = 295,
        SPELL_AURA_296                                      = 296,
        SPELL_AURA_297                                      = 297,
        SPELL_AURA_298                                      = 298,
        SPELL_AURA_299                                      = 299,
        SPELL_AURA_300                                      = 300,
        SPELL_AURA_HEAL_ABSORB                              = 301,
        SPELL_AURA_302                                      = 302,
        SPELL_AURA_303                                      = 303,
        SPELL_AURA_304                                      = 304,
        SPELL_AURA_MOD_MINIMUM_SPEED                        = 305,
        SPELL_AURA_306                                      = 306,
        SPELL_AURA_307                                      = 307,
        SPELL_AURA_308                                      = 308,
        SPELL_AURA_309                                      = 309,
        SPELL_AURA_MOD_PET_AOE_DAMAGE_AVOIDANCE             = 310,
        SPELL_AURA_311                                      = 311,
        SPELL_AURA_312                                      = 312,
        SPELL_AURA_313                                      = 313,
        SPELL_AURA_314                                      = 314,
        SPELL_AURA_315                                      = 315,
        SPELL_AURA_316                                      = 316
    };

    enum ShapeshiftFormMask
    {
        FORM_NONE               = 0,
        FORM_CAT                = 1 << 0x00,
        FORM_TREE               = 1 << 0x01,
        FORM_TRAVEL             = 1 << 0x02,
        FORM_AQUA               = 1 << 0x03,
        FORM_BEAR               = 1 << 0x04,
        FORM_AMBIENT            = 1 << 0x05,
        FORM_GHOUL              = 1 << 0x06,
        FORM_DIREBEAR           = 1 << 0x07,
        FORM_STEVES_GHOUL       = 1 << 0x08,
        FORM_THARONJA_SKELETON  = 1 << 0x09,
        FORM_TEST_OF_STRENGTH   = 1 << 0x0A,
        FORM_BLB_PLAYER         = 1 << 0x0B,
        FORM_SHADOW_DANCE       = 1 << 0x0C,
        FORM_CREATUREBEAR       = 1 << 0x0D,
        FORM_CREATURECAT        = 1 << 0x0E,
        FORM_GHOSTWOLF          = 1 << 0x0F,
        FORM_BATTLESTANCE       = 1 << 0x10,
        FORM_DEFENSIVESTANCE    = 1 << 0x11,
        FORM_BERSERKERSTANCE    = 1 << 0x12,
        FORM_TEST               = 1 << 0x13,
        FORM_ZOMBIE             = 1 << 0x14,
        FORM_METAMORPHOSIS      = 1 << 0x15,
        FORM_UNK1               = 1 << 0x16,
        FORM_UNK2               = 1 << 0x17,
        FORM_UNDEAD             = 1 << 0x18,
        FORM_FRENZY             = 1 << 0x19,
        FORM_FLIGHT_EPIC        = 1 << 0x1A,
        FORM_SHADOW             = 1 << 0x1B,
        FORM_FLIGHT             = 1 << 0x1C,
        FORM_STEALTH            = 1 << 0x1D,
        FORM_MOONKIN            = 1 << 0x1E,
        FORM_SPIRITOFREDEMPTION = 1 << 0x1F
    };

    enum ItemClass
    {
        CONSUMABLE  = 0,
        CONTAINER   = 1,
        WEAPONS     = 2,
        GEM         = 3,
        ARMOR       = 4,
        REAGENT     = 5,
        PROJECTILE  = 6,
        TRADE_GOODS = 7,
        GENERIC     = 8,
        RECIPE      = 9,
        MONEY       = 10,
        QUIVER      = 11,
        QUEST       = 12,
        KEY         = 13,
        PERMANENT   = 14,
        MISC        = 15,
        GLYPH       = 16,
        MAX
    };

    enum ItemSubClassWeaponMask
    {
        AXE           = 1 << 0x00,
        AXE2          = 1 << 0x01,
        BOW           = 1 << 0x02,
        GUN           = 1 << 0x03,
        MACE          = 1 << 0x04,
        MACE2         = 1 << 0x05,
        POLEARM       = 1 << 0x06,
        SWORD         = 1 << 0x07,
        SWORD2        = 1 << 0x08,
        OBSOLETE      = 1 << 0x09,
        STAFF         = 1 << 0x0A,
        EXOTIC        = 1 << 0x0B,
        EXOTIC2       = 1 << 0x0C,
        FIST          = 1 << 0x0D,
        MISC_WEAPON   = 1 << 0x0E,
        DAGGER        = 1 << 0x0F,
        THROWNS       = 1 << 0x10,
        SPEAR         = 1 << 0x11,
        CROSSBOW      = 1 << 0x12,
        WAND          = 1 << 0x13,
        FISHING_POLE  = 1 << 0x14
    };

    enum ItemSubClassArmorMask
    {
        MISC_ARMOR= 1 << 0x0,
        CLOTH     = 1 << 0x1,
        LEATHER   = 1 << 0x2,
        MAIL      = 1 << 0x3,
        PLATE     = 1 << 0x4,
        BUCKLER   = 1 << 0x5,
        SHIELD    = 1 << 0x6,
        LIBRAM    = 1 << 0x7,
        IDOL      = 1 << 0x8,
        TOTEM     = 1 << 0x9,
        SIGIL     = 1 << 0xA
    };

    enum ItemSubClassMiscMask
    {
        JUNK          = 1 << 0x0,
        MISC_REAGENT  = 1 << 0x1,
        PET           = 1 << 0x2,
        HOLIDAY       = 1 << 0x3,
        OTHER         = 1 << 0x4,
        MOUNT         = 1 << 0x5,
    };

    enum InventoryTypeMask
    {
        NON_EQUIP       = 1 << 0x00,
        HEAD            = 1 << 0x01,
        NECK            = 1 << 0x02,
        SHOULDERS       = 1 << 0x03,
        BODY            = 1 << 0x04,
        CHEST           = 1 << 0x05,
        WAIST           = 1 << 0x06,
        LEGS            = 1 << 0x07,
        FEET            = 1 << 0x08,
        WRISTS          = 1 << 0x09,
        HANDS           = 1 << 0x0A,
        FINGER          = 1 << 0x0B,
        TRINKET         = 1 << 0x0C,
        WEAPON          = 1 << 0x0D,
        SHIELD_INV      = 1 << 0x0E,
        RANGED          = 1 << 0x0F,
        CLOAK           = 1 << 0x10,
        WEAPON_2H       = 1 << 0x11,
        BAG             = 1 << 0x12,
        TABARD          = 1 << 0x13,
        ROBE            = 1 << 0x14,
        WEAPONMAINHAND  = 1 << 0x15,
        WEAPONOFFHAND   = 1 << 0x16,
        HOLDABLE        = 1 << 0x17,
        AMMO            = 1 << 0x18,
        THROWN          = 1 << 0x19,
        RANGEDRIGHT     = 1 << 0x1A,
        QUIVER_INV      = 1 << 0x1B,
        RELIC           = 1 << 0x1C,
    };

    enum CombatRating
    {
        CR_WEAPON_SKILL             =      0x00,
        CR_DEFENSE_SKILL            = 1 << 0x00,
        CR_DODGE                    = 1 << 0x01,
        CR_PARRY                    = 1 << 0x02,
        CR_BLOCK                    = 1 << 0x03,
        CR_HIT_MELEE                = 1 << 0x04,
        CR_HIT_RANGED               = 1 << 0x05,
        CR_HIT_SPELL                = 1 << 0x06,
        CR_CRIT_MELEE               = 1 << 0x07,
        CR_CRIT_RANGED              = 1 << 0x08,
        CR_CRIT_SPELL               = 1 << 0x09,
        CR_HIT_TAKEN_MELEE          = 1 << 0x0A,
        CR_HIT_TAKEN_RANGED         = 1 << 0x0B,
        CR_HIT_TAKEN_SPELL          = 1 << 0x0C,
        CR_CRIT_TAKEN_MELEE         = 1 << 0x0D,
        CR_CRIT_TAKEN_RANGED        = 1 << 0x0E,
        CR_CRIT_TAKEN_SPELL         = 1 << 0x0F,
        CR_HASTE_MELEE              = 1 << 0x10,
        CR_HASTE_RANGED             = 1 << 0x11,
        CR_HASTE_SPELL              = 1 << 0x12,
        CR_WEAPON_SKILL_MAINHAND    = 1 << 0x13,
        CR_WEAPON_SKILL_OFFHAND     = 1 << 0x14,
        CR_WEAPON_SKILL_RANGED      = 1 << 0x15,
        CR_EXPERTISE                = 1 << 0x16,
        CR_ARMOR_PENETRATION        = 1 << 0x17,
    };

    enum DispelType
    {
        DISPEL_NONE         = 0,
        DISPEL_MAGIC        = 1,
        DISPEL_CURSE        = 2,
        DISPEL_DISEASE      = 3,
        DISPEL_POISON       = 4,
        DISPEL_STEALTH      = 5,
        DISPEL_INVISIBILITY = 6,
        DISPEL_ALL          = 7,
        DISPEL_SPE_NPC_ONLY = 8,
        DISPEL_ENRAGE       = 9,
        DISPEL_ZG_TICKET    = 10,
        DESPEL_OLD_UNUSED   = 11
    };

    enum AuraState
    {
        AURA_STATE_NONE                     = 0,
        AURA_STATE_DEFENSE                  = 1,
        AURA_STATE_HEALTHLESS_20_PERCENT    = 2,
        AURA_STATE_BERSERKING               = 3,
        AURA_STATE_FROZEN                   = 4,
        AURA_STATE_JUDGEMENT                = 5,
        AURA_STATE_UNKNOWN6                 = 6,
        AURA_STATE_HUNTER_PARRY             = 7,
        AURA_STATE_UNKNOWN8                 = 8,
        AURA_STATE_UNKNOWN9                 = 9,
        AURA_STATE_WARRIOR_VICTORY_RUSH     = 10,
        AURA_STATE_UNKNOWN11                = 11,
        AURA_STATE_FAERIE_FIRE              = 12,
        AURA_STATE_HEALTHLESS_35_PERCENT    = 13,
        AURA_STATE_CONFLAGRATE              = 14,
        AURA_STATE_SWIFTMEND                = 15,
        AURA_STATE_DEADLY_POISON            = 16,
        AURA_STATE_ENRAGE                   = 17,
        AURA_STATE_UNKNOWN18                = 18,
        AURA_STATE_UNKNOWN19                = 19,
        AURA_STATE_UNKNOWN20                = 20,
        AURA_STATE_UNKNOWN21                = 21,
        AURA_STATE_UNKNOWN22                = 22,
        AURA_STATE_HEALTH_ABOVE_75_PERCENT  = 23

    };

    enum Targets
    {
        NO_TARGET                               = 0,
        TARGET_SELF                             = 1,
        TARGET_RANDOM_ENEMY_CHAIN_IN_AREA       = 2,
        TARGET_RANDOM_FRIEND_CHAIN_IN_AREA      = 3,
        TARGET_4                                = 4,
        TARGET_PET                              = 5,
        TARGET_CHAIN_DAMAGE                     = 6,
        TARGET_AREAEFFECT_INSTANT               = 7,
        TARGET_AREAEFFECT_CUSTOM                = 8,
        TARGET_INNKEEPER_COORDINATES            = 9,
        TARGET_10                               = 10,
        TARGET_11                               = 11,
        TARGET_12                               = 12,
        TARGET_13                               = 13,
        TARGET_14                               = 14,
        TARGET_ALL_ENEMY_IN_AREA                = 15,
        TARGET_ALL_ENEMY_IN_AREA_INSTANT        = 16,
        TARGET_TABLE_X_Y_Z_COORDINATES          = 17,
        TARGET_EFFECT_SELECT                    = 18,
        TARGET_19                               = 19,
        TARGET_ALL_PARTY_AROUND_CASTER          = 20,
        TARGET_SINGLE_FRIEND                    = 21,
        TARGET_CASTER_COORDINATES               = 22,
        TARGET_GAMEOBJECT                       = 23,
        TARGET_IN_FRONT_OF_CASTER               = 24,
        TARGET_DUELVSPLAYER                     = 25,
        TARGET_GAMEOBJECT_ITEM                  = 26,
        TARGET_MASTER                           = 27,
        TARGET_ALL_ENEMY_IN_AREA_CHANNELED      = 28,
        TARGET_29                               = 29,
        TARGET_ALL_FRIENDLY_UNITS_AROUND_CASTER = 30,
        TARGET_ALL_FRIENDLY_UNITS_IN_AREA       = 31,
        TARGET_MINION                           = 32,
        TARGET_ALL_PARTY                        = 33,
        TARGET_ALL_PARTY_AROUND_CASTER_2        = 34,
        TARGET_SINGLE_PARTY                     = 35,
        TARGET_ALL_HOSTILE_UNITS_AROUND_CASTER  = 36,
        TARGET_AREAEFFECT_PARTY                 = 37,
        TARGET_SCRIPT                           = 38,
        TARGET_SELF_FISHING                     = 39,
        TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT     = 40,
        TARGET_TOTEM_EARTH                      = 41,
        TARGET_TOTEM_WATER                      = 42,
        TARGET_TOTEM_AIR                        = 43,
        TARGET_TOTEM_FIRE                       = 44,
        TARGET_CHAIN_HEAL                       = 45,
        TARGET_SCRIPT_COORDINATES               = 46,
        TARGET_DYNAMIC_OBJECT_FRONT             = 47,
        TARGET_DYNAMIC_OBJECT_BEHIND            = 48,
        TARGET_DYNAMIC_OBJECT_LEFT_SIDE         = 49,
        TARGET_DYNAMIC_OBJECT_RIGHT_SIDE        = 50,
        TARGET_51                               = 51,
        TARGET_AREAEFFECT_GO_AROUND_DEST        = 52,
        TARGET_CURRENT_ENEMY_COORDINATES        = 53,
        TARGET_LARGE_FRONTAL_CONE               = 54,
        TARGET_55                               = 55,
        TARGET_ALL_RAID_AROUND_CASTER           = 56,
        TARGET_SINGLE_FRIEND_2                  = 57,
        TARGET_58                               = 58,
        TARGET_59                               = 59,
        TARGET_NARROW_FRONTAL_CONE              = 60,
        TARGET_AREAEFFECT_PARTY_AND_CLASS       = 61,
        TARGET_62                               = 62,
        TARGET_DUELVSPLAYER_COORDINATES         = 63,
        TARGET_INFRONT_OF_VICTIM                = 64,
        TARGET_BEHIND_VICTIM                    = 65,
        TARGET_RIGHT_FROM_VICTIM                = 66,
        TARGET_LEFT_FROM_VICTIM                 = 67,
        TARGET_68                               = 68,
        TARGET_69                               = 69,
        TARGET_70                               = 70,
        TARGET_71                               = 71,
        TARGET_RANDOM_NEARBY_LOC                = 72,
        TARGET_RANDOM_CIRCUMFERENCE_POINT       = 73,
        TARGET_74                               = 74,
        TARGET_75                               = 75,
        TARGET_DYNAMIC_OBJECT_COORDINATES       = 76,
        TARGET_SINGLE_ENEMY                     = 77,
        TARGET_POINT_AT_NORTH                   = 78,
        TARGET_POINT_AT_SOUTH                   = 79,
        TARGET_POINT_AT_EAST                    = 80,
        TARGET_POINT_AT_WEST                    = 81,
        TARGET_POINT_AT_NE                      = 82,
        TARGET_POINT_AT_NW                      = 83,
        TARGET_POINT_AT_SE                      = 84,
        TARGET_POINT_AT_SW                      = 85,
        TARGET_RANDOM_NEARBY_DEST               = 86,
        TARGET_SELF2                            = 87,
        TARGET_88                               = 88,
        TARGET_DIRECTLY_FORWARD                 = 89,
        TARGET_NONCOMBAT_PET                    = 90,
        TARGET_91                               = 91,
        TARGET_92                               = 92,
        TARGET_93                               = 93,
        TARGET_94                               = 94,
        TARGET_95                               = 95,
        TARGET_96                               = 96,
        TARGET_97                               = 97,
        TARGET_98                               = 98,
        TARGET_99                               = 99,
        TARGET_100                              = 100,
        TARGET_101                              = 101,
        TARGET_102                              = 102,
        TARGET_103                              = 103,
        TARGET_IN_FRONT_OF_CASTER_30            = 104
    };

    enum UnitMods
    {
        UNIT_MOD_STAT_STRENGTH          = 0,
        UNIT_MOD_STAT_AGILITY           = 1,
        UNIT_MOD_STAT_STAMINA           = 2,
        UNIT_MOD_STAT_INTELLECT         = 3,
        UNIT_MOD_STAT_SPIRIT            = 4,
        UNIT_MOD_HEALTH                 = 5,
        UNIT_MOD_MANA                   = 6,
        UNIT_MOD_RAGE                   = 7,
        UNIT_MOD_FOCUS                  = 8,
        UNIT_MOD_ENERGY                 = 9,
        UNIT_MOD_HAPPINESS              = 10,
        UNIT_MOD_RUNE                   = 11,
        UNIT_MOD_RUNIC_POWER            = 12,
        UNIT_MOD_ARMOR                  = 13,
        UNIT_MOD_RESISTANCE_HOLY        = 14,
        UNIT_MOD_RESISTANCE_FIRE        = 15,
        UNIT_MOD_RESISTANCE_NATURE      = 16,
        UNIT_MOD_RESISTANCE_FROST       = 17,
        UNIT_MOD_RESISTANCE_SHADOW      = 18,
        UNIT_MOD_RESISTANCE_ARCANE      = 19,
        UNIT_MOD_ATTACK_POWER           = 20,
        UNIT_MOD_ATTACK_POWER_RANGED    = 21,
        UNIT_MOD_DAMAGE_MAINHAND        = 22,
        UNIT_MOD_DAMAGE_OFFHAND         = 23,
        UNIT_MOD_DAMAGE_RANGED          = 24,
        UNIT_MOD_END                    = 25,
        // synonyms
        UNIT_MOD_STAT_START             = UNIT_MOD_STAT_STRENGTH,
        UNIT_MOD_STAT_END               = UNIT_MOD_STAT_SPIRIT       + 1,
        UNIT_MOD_RESISTANCE_START       = UNIT_MOD_ARMOR,
        UNIT_MOD_RESISTANCE_END         = UNIT_MOD_RESISTANCE_ARCANE + 1,
        UNIT_MOD_POWER_START            = UNIT_MOD_MANA,
        UNIT_MOD_POWER_END              = UNIT_MOD_RUNIC_POWER       + 1
    };

    enum SpellModOp
    {
        SPELLMOD_DAMAGE                 = 0,
        SPELLMOD_DURATION               = 1,
        SPELLMOD_THREAT                 = 2,
        SPELLMOD_EFFECT1                = 3,
        SPELLMOD_CHARGES                = 4,
        SPELLMOD_RANGE                  = 5,
        SPELLMOD_RADIUS                 = 6,
        SPELLMOD_CRITICAL_CHANCE        = 7,
        SPELLMOD_ALL_EFFECTS            = 8,
        SPELLMOD_NOT_LOSE_CASTING_TIME  = 9,
        SPELLMOD_CASTING_TIME           = 10,
        SPELLMOD_COOLDOWN               = 11,
        SPELLMOD_EFFECT2                = 12,
        SPELLMOD_13                     = 13,
        SPELLMOD_COST                   = 14,
        SPELLMOD_CRIT_DAMAGE_BONUS      = 15,
        SPELLMOD_RESIST_MISS_CHANCE     = 16,
        SPELLMOD_JUMP_TARGETS           = 17,
        SPELLMOD_CHANCE_OF_SUCCESS      = 18,
        SPELLMOD_ACTIVATION_TIME        = 19,
        SPELLMOD_EFFECT_PAST_FIRST      = 20,
        SPELLMOD_CASTING_TIME_OLD       = 21,
        SPELLMOD_DOT                    = 22,
        SPELLMOD_EFFECT3                = 23,
        SPELLMOD_SPELL_BONUS_DAMAGE     = 24,
        SPELLMOD_25                     = 25,
        SPELLMOD_FREQUENCY_OF_SUCCESS   = 26,
        SPELLMOD_MULTIPLE_VALUE         = 27,
        SPELLMOD_RESIST_DISPEL_CHANCE   = 28
    };

    enum SpellFamilyNames
    {
        SPELLFAMILY_GENERIC     = 0,
        SPELLFAMILY_UNK1        = 1,
        // unused               = 2,
        SPELLFAMILY_MAGE        = 3,
        SPELLFAMILY_WARRIOR     = 4,
        SPELLFAMILY_WARLOCK     = 5,
        SPELLFAMILY_PRIEST      = 6,
        SPELLFAMILY_DRUID       = 7,
        SPELLFAMILY_ROGUE       = 8,
        SPELLFAMILY_HUNTER      = 9,
        SPELLFAMILY_PALADIN     = 10,
        SPELLFAMILY_SHAMAN      = 11,
        SPELLFAMILY_UNK2        = 12,
        SPELLFAMILY_POTION      = 13,
        // unused               = 14,
        SPELLFAMILY_DEATHKNIGHT = 15,

        // unused               = 16,
        SPELLFAMILY_PET         = 17
    };

    enum Powers
    {
        POWER_MANA          = 0,
        POWER_RAGE          = 1,
        POWER_FOCUS         = 2,
        POWER_ENERGY        = 3,
        POWER_HAPPINESS     = 4,
        POWER_RUNE          = 5,
        POWER_RUNIC_POWER   = 6,
        POWER_HEALTH        = -2,
    };

    Q_ENUMS(LocalesDBC)
    Q_ENUMS(Mechanic)
    Q_ENUMS(PreventionType)
    Q_ENUMS(DamageClass)
    Q_ENUMS(SpellSchoolMask)
    Q_ENUMS(Effects)
    Q_ENUMS(TargetFlags)
    Q_ENUMS(CreatureTypeMask)
    Q_ENUMS(Attributes)
    Q_ENUMS(AttributesEx)
    Q_ENUMS(AttributesEx2)
    Q_ENUMS(AttributesEx3)
    Q_ENUMS(AttributesEx4)
    Q_ENUMS(AttributesEx5)
    Q_ENUMS(AttributesEx6)
    Q_ENUMS(AttributesEx7)
    Q_ENUMS(AuraType)
    Q_ENUMS(ShapeshiftFormMask)
    Q_ENUMS(ItemClass)
    Q_ENUMS(ItemSubClassWeaponMask)
    Q_ENUMS(ItemSubClassArmorMask)
    Q_ENUMS(ItemSubClassMiscMask)
    Q_ENUMS(InventoryTypeMask)
    Q_ENUMS(CombatRating)
    Q_ENUMS(DispelType)
    Q_ENUMS(AuraState)
    Q_ENUMS(Targets)
    Q_ENUMS(UnitMods)
    Q_ENUMS(SpellModOp)
    Q_ENUMS(SpellFamilyNames)
    Q_ENUMS(Powers)
};


#endif
