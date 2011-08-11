#pragma once

/*
 *      Copyright (C) 2005-2010 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "addons/include/xbmc_pvr_types.h"
#include "XBDateTime.h"
#include "Epg.h"

namespace PVR
{
  class CPVRTimerInfoTag;
}

/** an EPG info tag */
namespace EPG
{
  class CEpg;

  class CEpgInfoTag
  {
    friend class CEpg;
    friend class CEpgDatabase;

  public:
    /*!
     * @brief Create a new EPG event.
     * @param iUniqueBroadcastId The unique broadcast ID for this event.
     */
    CEpgInfoTag(int iUniqueBroadcastId);

    /*!
     * @brief Create a new empty event without a unique ID.
     */
    CEpgInfoTag();

    /*!
     * @brief Create a new EPG infotag with 'data' as content.
     * @param data The tag's content.
     */
    CEpgInfoTag(const EPG_TAG &data);

    /*!
     * @brief Destroy this instance.
     */
    virtual ~CEpgInfoTag();

    bool operator ==(const CEpgInfoTag& right) const;
    bool operator !=(const CEpgInfoTag& right) const;

    /*!
     * @brief Check whether this tag has changed and unsaved values.
     * @return True if it has unsaved values, false otherwise.
     */
    virtual bool Changed(void) const { return m_bChanged; }

    /*!
     * @brief The table this event belongs to
     * @return The table this event belongs to
     */
    virtual const CEpg *GetTable() const { return m_Epg; }

    /*!
     * @brief Change the unique broadcast ID of this event.
     * @param iUniqueBroadcastId The new unique broadcast ID.
     */
    virtual void SetUniqueBroadcastID(int iUniqueBroadcastID);

    /*!
     * @brief Get the unique broadcast ID.
     * @return The unique broadcast ID.
     */
    virtual int UniqueBroadcastID(void) const { return m_iUniqueBroadcastID; }

    /*!
     * @brief Get the event's database ID.
     * @return The database ID.
     */
    virtual int BroadcastId(void) const { return m_iBroadcastId; }

    /*!
     * @brief Change the event's database ID.
     * @param iId The new database ID.
     */
    virtual void SetBroadcastId(int iId);

    /*!
     * @brief Get the event's start time.
     * @return The new start time.
     */
    virtual const CDateTime &StartAsUTC(void) const { return m_startTime; }
    virtual const CDateTime &StartAsLocalTime(void) const;

    /*!
     * @brief Change the event's start time.
     * @param start The new start time.
     */
    virtual void SetStartFromUTC(const CDateTime &start);
    void SetStartFromLocalTime(const CDateTime &start);

    /*!
     * @brief Get the event's end time.
     * @return The new start time.
     */
    virtual const CDateTime &EndAsUTC(void) const { return m_endTime; }
    virtual const CDateTime &EndAsLocalTime(void) const;

    /*!
     * @brief Change the event's end time.
     * @param end The new end time.
     */
    virtual void SetEndFromUTC(const CDateTime &end);
    virtual void SetEndFromLocalTime(const CDateTime &end);

    /*!
     * @brief Get the duration of this event in seconds.
     * @return The duration in seconds.
     */
    virtual int GetDuration() const;

    /*!
     * @brief Get the title of this event.
     * @return The title.
     */
    virtual const CStdString &Title(void) const;

    /*!
     * @brief Change the title of this event.
     * @param strTitle The new title.
     */
    virtual void SetTitle(const CStdString &strTitle);

    /*!
     * @brief Get the plot outline of this event.
     * @return The plot outline.
     */
    virtual const CStdString &PlotOutline(void) const { return m_strPlotOutline; }

    /*!
     * @brief Change the plot outline of this event.
     * @param strPlotOutline The new plot outline.
     */
    virtual void SetPlotOutline(const CStdString &strPlotOutline);

    /*!
     * @brief Get the plot of this event.
     * @return The plot.
     */
    virtual const CStdString &Plot(void) const { return m_strPlot; }

    /*!
     * @brief Change the plot of this event.
     * @param strPlot The new plot.
     */
    virtual void SetPlot(const CStdString &strPlot);

    /*!
     * @brief Get the genre type ID of this event.
     * @return The genre type ID.
     */
    virtual int GenreType(void) const { return m_iGenreType; }

    /*!
     * @brief Get the genre subtype ID of this event.
     * @return The genre subtype ID.
     */
    int GenreSubType(void) const { return m_iGenreSubType; }

    /*!
     * @brief Get the genre as human readable string.
     * @return The genre.
     */
    virtual const CStdString &Genre(void) const { return m_strGenre; }

    /*!
     * @brief Change the genre of this event.
     * @param iID The genre type ID.
     * @param iSubID The genre subtype ID.
     */
    virtual void SetGenre(int iID, int iSubID, const char* strGenre);

    /*!
     * @brief Get the first air date of this event.
     * @return The first air date.
     */
    virtual const CDateTime &FirstAiredAsUTC(void) const { return m_firstAired; }
    virtual const CDateTime &FirstAiredAsLocalTime(void) const;

    /*!
     * @brief Change the first air date of this event.
     * @param firstAired The new first air date.
     */
    virtual void SetFirstAiredFromUTC(const CDateTime &firstAired);
    virtual void SetFirstAiredFromLocalTime(const CDateTime &firstAired);

    /*!
     * @brief Get the parental rating of this event.
     * @return The parental rating.
     */
    virtual int ParentalRating(void) const { return m_iParentalRating; }

    /*!
     * @brief Change the parental rating of this event.
     * @param iParentalRating The new parental rating.
     */
    virtual void SetParentalRating(int iParentalRating);

    /*!
     * @brief Get the star rating of this event.
     * @return The star rating.
     */
    virtual int StarRating(void) const { return m_iStarRating; }

    /*!
     * @brief Change the star rating of this event.
     * @param iStarRating The new star rating.
     */
    virtual void SetStarRating(int iStarRating);

    /*!
     * @brief Notify on start if true.
     * @return Notify on start.
     */
    virtual bool Notify(void) const { return m_bNotify; }

    /*!
     * @brief Change the value of notify on start.
     * @param bNotify The new value.
     */
    virtual void SetNotify(bool bNotify);

    /*!
     * @brief The series number of this event.
     * @return The series number.
     */
    virtual int SeriesNum(void) const { return m_iSeriesNumber; }

    /*!
     * @brief Change the series number of this event.
     * @param strSeriesNum The new series number.
     */
    virtual void SetSeriesNum(int iSeriesNum);

    /*!
     * @brief The episode number of this event.
     * @return The episode number.
     */
    virtual int EpisodeNum(void) const { return m_iEpisodeNumber; }

    /*!
     * @brief Change the episode number of this event.
     * @param strEpisodeNum The new episode number.
     */
    virtual void SetEpisodeNum(int iEpisodeNum);

    /*!
     * @brief The episode part number of this event.
     * @return The episode part number.
     */
    virtual int EpisodePart(void) const { return m_iEpisodePart; }

    /*!
     * @brief Change the episode part number of this event.
     * @param strEpisodePart The new episode part number.
     */
    virtual void SetEpisodePart(int iEpisodePart);

    /*!
     * @brief The episode name of this event.
     * @return The episode name.
     */
    virtual const CStdString &EpisodeName(void) const { return m_strEpisodeName; }

    /*!
     * @brief Change the episode name of this event.
     * @param strEpisodeName The new episode name.
     */
    virtual void SetEpisodeName(const CStdString &strEpisodeName);

    /*!
     * @brief Get the path to the icon for this event.
     * @return The path to the icon
     */
    virtual const CStdString &Icon(void) const;

    /*!
     * @brief Change the path to the icon for this event.
     * @param strIconPath The new path.
     */
    virtual void SetIcon(const CStdString &strIconPath);

    /*!
     * @brief The path to this event.
     * @return The path.
     */
    virtual const CStdString &Path(void) const { return m_strFileNameAndPath; }

    /*!
     * @brief Change the path to this event.
     * @param strFileNameAndPath The new path.
     */
    virtual void SetPath(const CStdString &strFileNameAndPath);

    /*!
     * @brief Get a pointer to the next event. Set by CEpg in a call to Sort()
     * @return A pointer to the next event or NULL if it's not set.
     */
    virtual const CEpgInfoTag *GetNextEvent() const;

    /*!
     * @brief Get a pointer to the previous event. Set by CEpg in a call to Sort()
     * @return A pointer to the previous event or NULL if it's not set.
     */
    virtual const CEpgInfoTag *GetPreviousEvent() const;

    /*!
     * @brief Update the information in this tag with the info in the given tag.
     * @param tag The new info.
     * @return True if something changed, false otherwise.
     */
    virtual bool Update(const CEpgInfoTag &tag);

    /*!
     * @brief Check if this event is currently active.
     * @return True if it's active, false otherwise.
     */
    virtual bool IsActive(void) const;

    /*!
     * @brief Persist this tag in the database.
     * @param bSingleUpdate True if this is a single update, false if more updates will follow.
     * @param bLastUpdate True to commit a batch of changes, false otherwise.
     * @return True if the tag was persisted correctly, false otherwise.
     */
    virtual bool Persist(bool bSingleUpdate = true, bool bLastUpdate = false);

    /*!
     * @return The current progress of this tag.
     */
    virtual float ProgressPercentage(void) const;

    /*!
     * @brief Check whether this event has an active timer tag.
     * @return True if it has an active timer tag, false if not.
     */
    virtual bool HasTimer() const { return !(m_Timer == NULL); }

    virtual bool HasPVRChannel(void) const;

    /*!
     * @brief Set a timer for this event or NULL to clear it.
     * @param newTimer The new timer value.
     */
    virtual void SetTimer(const PVR::CPVRTimerInfoTag *newTimer) { m_Timer = newTimer; }

    /*!
     * @brief Get a pointer to the timer for event or NULL if there is none.
     * @return A pointer to the timer for event or NULL if there is none.
     */
    virtual const PVR::CPVRTimerInfoTag *Timer(void) const { return m_Timer; }

    /*!
     * @brief Update the information in this tag with the info in the given tag.
     * @param tag The new info.
     */
    virtual void Update(const EPG_TAG &tag);

    /*!
     * @brief Get the channel that plays this event.
     * @return a pointer to the channel.
     */
    virtual const PVR::CPVRChannel *ChannelTag(void) const;

  protected:
    /*!
     * @brief Hook that is called when the start date changed.
     */
    virtual void UpdatePath();

    /*!
     * @brief Change the pointer to the next event.
     * @param event The next event.
     */
    virtual void SetNextEvent(const CEpgInfoTag *event) { m_nextEvent = event; }

    /*!
     * @brief Change the pointer to the previous event.
     * @param event The previous event.
     */
    virtual void SetPreviousEvent(const CEpgInfoTag *event) { m_previousEvent = event; }

    bool                         m_bNotify;            /*!< notify on start */
    bool                         m_bChanged;           /*!< keep track of changes to this entry */

    int                          m_iBroadcastId;       /*!< database ID */
    int                          m_iGenreType;         /*!< genre type */
    int                          m_iGenreSubType;      /*!< genre subtype */
    int                          m_iParentalRating;    /*!< parental rating */
    int                          m_iStarRating;        /*!< star rating */
    int                          m_iSeriesNumber;      /*!< series number */
    int                          m_iEpisodeNumber;     /*!< episode number */
    int                          m_iEpisodePart;       /*!< episode part number */
    int                          m_iUniqueBroadcastID; /*!< unique broadcast ID */
    CStdString                   m_strTitle;           /*!< title */
    CStdString                   m_strPlotOutline;     /*!< plot outline */
    CStdString                   m_strPlot;            /*!< plot */
    CStdString                   m_strGenre;           /*!< genre */
    CStdString                   m_strEpisodeName;     /*!< episode name */
    CStdString                   m_strIconPath;        /*!< the path to the icon */
    CStdString                   m_strFileNameAndPath; /*!< the filename and path */
    CDateTime                    m_startTime;          /*!< event start time */
    CDateTime                    m_endTime;            /*!< event end time */
    CDateTime                    m_firstAired;         /*!< first airdate */

    mutable const CEpgInfoTag *  m_nextEvent;          /*!< the event that will occur after this one */
    mutable const CEpgInfoTag *  m_previousEvent;      /*!< the event that occurred before this one */

    const PVR::CPVRTimerInfoTag *m_Timer;              /*!< a pointer to a timer for this event or NULL if there is none */
    const CEpg *                 m_Epg;                /*!< the schedule this event belongs to */
  };
}
