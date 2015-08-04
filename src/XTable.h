/****************************************************************************
 * XTable.h - Class for Arduino sketches                                    *
 * Copyright (C) 2014 by AF                                  				*
 *                                                                          *
 * This file is part of AF Support                                          *
 *                                                                          *
 *   XTable is free software: you can redistribute it and/or modify it      *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   XTable is distributed in the hope that it will be useful,              *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with XTable. If not, see <http://www.gnu.org/licenses/>. *
 ****************************************************************************/

/**
 *  @file    XTable.h
 *  @author  AF
 *  @date    08/2015
 *  @version 2.0
 *
 *	@brief CRUD table as persistent storage implementation for embedded devices
 *
 *  @section DESCRIPTION
 *
 *  This class support short set of informations, typically for configuration
 *  purpose, with CRUD API approach (Create, Read, Update and Delete).
 *  It manages generic structured items through an efficient storage using a
 *  circular buffer in EEPROM and volatile SRAM.
 *
 */


#include "XEEPROM/XEEPROM.h"

#ifndef XTable_H_
#define XTable_H_

#ifndef NULL
#define NULL 0
#endif


template <class X> class XTable
{
  public:

    const unsigned char BMK = 0x42;
    const unsigned char EMK = 0x45;

    /// Default constructor
    XTable();

    /// Default destructor
    ~XTable();

    /**
     * @brief Initialize buffer on SRAM to manage maximum expected items
     *
     * @param max_items specify maximum size of the buffer
     * @retval true successfully created the new buffer
     * @retval false unsuccess. Required buffer cannot be created
     */
    bool InitBuffer(int max_items);


    /**
     * @brief Method to add new data into the table.
     *
     * This method provides CRUD operation to create new data
     * at the end of current table. It creates specified item into runtime
     * list on SRAM. Automatic index (positive integer) is assigned
     * to the new entry providing quicker access to data. The index
     * increase of 1 unit last available id on current table.
     *
     * @param X specify the new entry to add into the table
     * @retval true successfully created the new entry
     * @retval false unsuccess. Required entry cannot be created
     */
    bool Insert(X item);
    
    /**
     * @brief Method to read current item on the table.
     *
     * This method provides CRUD operation to read the item
     * available on the table at current list position.
     *
     * @param None
     * @retval X entry at current position on the table
     * @retval NULL for empty list
     */
    X* Select();

    /**
     * @brief Method to update current item on the table.
     *
     * This method provides CRUD operation to update the item
     * available on the table at current list position.
     *
     * @param X specify the new entry to update into the table
     * @retval true successfully updated current entry
     * @retval false unsuccess. Empty list.
     */
    bool Update(X item);

    /**
     * @brief Method to delete current item from the table.
     *
     * This method provides CRUD operation to delete the item
     * available on the table at current list position.
     *
     * @param None
     * @retval true successfully deleted current entry
     * @retval false unsuccess. Empty list.
     */
    bool Delete();

    /**
     * @brief Method to remove all available entries from the table
     *
     * This method clean current table. It removes all available entries
     * existing over runtime list on SRAM.
     *
     * @param None
     * @retval None
     */
    void Clean();

    /**
     * @brief Method to counting all available entries
     *
     * This method provides the number of all available entries depending
     * on their status. This operation is status sensitive. This means
     * that it provides the number of all existing entries or only
     * the entries enabled to be considered in the CRUD operations.
     *
     * @param None
     * @retval counter as positive integer of all available entries.
     */
    unsigned int Counter();

    /**
     * @brief Method to move current table position to the first entry.
     *
     * This method move current table position to the top. It puts current
     * entry position to the first one available over runtime list on SRAM.
     *
     * @param None
     * @retval true successfully moved to the top of list
     * @retval false unsuccess. Empty list.
     *
     */
    bool Top();

    /**
     * @brief Method to move current table position to the next entry.
     *
     * This method move current table position to the next. It puts current
     * entry position to the next one available over runtime list on SRAM.
     *
     * @param None
     * @retval true successfully moved to the next item
     * @retval false unsuccess. Empty list.
     */
    bool Next();

    /**
     * @brief Method to format specified EEPROM area for circular buffer management.
     *
     * This method format the EEPROM memory starting from specified address. It creates
     * two different sections: ones related to circular buffer status and another to keep all raw data.\n
     *
     * General memory structure:
     * <table border="0">
     * <tr><th></th><th>HEADER</th><th></th><th></th><th>DATA</th></tr>
     * <tr><th>Marker</th><td>Buf.Size</td><td>Status Buffer</td><td>Marker</td><td>Parameter Buffer</td></tr>
     * <tr><th>0</th><td>1</td><td></td><td>Buf.Size+2</td><td></td></tr>
     * <tr><th>(0x42)</th><td>(<size>)</td><td>(x) (x) (x) (x) ... (x) (x) (x)</td><td>(0x45)</td><td>(<data>) ... (<data>) ... (<data>)</td></tr>
     * </table>
     *
     * Where:\n
     * 		"Marker" identifiers boundaries (0 and <buffer_size>+2 locations) of the Status Buffer
     * 				 or Header portion of memory.\n
     * 		"Buf.Size" identify the buffer size or max number of available items inside the table.\n
     *
     * Please consider the Atmel Application Note AVR101 "High Endurance EEPROM Storage" for more
     * details about this implementation.
     *
     * @param start_location describe the start EEPROM address of the circular buffer
     * @param max_items describe maximum number of entries for the table
     * @retval true EEPROM successfully formatted. Specified area is ready for circular management
     * @retval false unsuccess. Required storage cannot be prepared because of size or unavailable EEPROM
     */
    bool InitStorage(int start_location, int max_items);


    /**
     * @brief Method to store current collection of items from the SRAM to the circular EEPROM storage.
     *
     * This method allow to store current items available inside the table into the already formatted
     * circular EEPROM storage. It allow to use the same EEPROM area improving the number of times the
     * data can be stored until to twice the expected limit through static approach.
     *
     * @param all_items pointer allocating the table. Pointer to the runtime list on SRAM
     * @retval true table stored into the EEPROM as expected
     * @retval false unsuccess. Items cannot be stored into expected EEPROM area
     */
    bool SaveStorage();

    /**
     * @brief Method to copy current collection of items from circular EEPROM storage to the runtime list on SRAM
     *
     * This method allow to read current items from circular EEPROM storage and copy them to the runtime list on SRAM.
     *
     * @param all_items pointer allocating the table. Pointer to the runtime list on SRAM
     * @retval true table copied from the EEPROM to the runtime list on SRAM as expected
     * @retval false unsuccess. Items cannot be read as expected from EEPROM area
     */
    bool LoadStorage();

    /**
      * @brief Method to get the top address of the area reserved to raw data or parameters
      *
      * @param None
      * @retval address of the location at the top of Parameter Buffer
      */
    int GetTopAddressStorage();

    /**
      * @brief Method to get the next available address beyond current used EEPROM
      *
      * @param None
      * @retval address of the next available location
      */
    int NextFreeAddressStorage();

    /// General structure to encapsulate each element with their <status> and <id>
    template <typename Y>
    struct XItem
    {
        Y item;
        bool enabled;
    };

    /// Shared instance of pointer to manage the Arduino EEPROM
    XItem<X> *xitem;
    XEEPROM< XItem<X> > eeprom;


  private:

    /// General structure to encapsulate each element of the table into runtime list on SRAM
    template <typename Y>
    struct Item
    {
        Y item;
        bool enabled;
        Item<Y> *next;
    };

    unsigned int counter;
    unsigned int buffer_max_items;

    Item<X> *first_record;
    Item<X> *current_record;
    Item<X> *new_record;

    /**< EEPROM Section */
    int eeprom_header_begin;
    int eeprom_parameter_begin;
    int eeprom_max_items;
    int top_status_ptr;
    int top_parameter_ptr;

    void Init();

    int IncCurrentLocation(int curr_location);

    int GetLocationFromStatus(int curr_location);

    void GetTopLocation();

    void PutTopLocation();

    /**
     * @brief Method to check the format of the storage and get current start point of circular buffer.
     *
     * This method check specified EEPROM as expected for circular buffer storage. It checks both markers
     * of the header section considering maximum number of specified entries.
     *
     * @param start_location describe the start EEPROM address of the circular buffer
     * @param max_items describe maximum number of entries for the table
     * @retval true EEPROM well defined. Specified area is formated as expected
     * @retval false unsuccess. Required storage is unformatted as expected
     */
    bool CheckStorage();
};


/******************************************************************************
 * User API
 ******************************************************************************/

template <class X> XTable<X>::XTable()
{
    // Initialize main global list pointers
    Init();

    //current_free_record = NULL;
    first_record = NULL;

    // Flag for InitStorage process
    eeprom_max_items = -1;
}

template <class X> XTable<X>::~XTable()
{
	current_record = first_record;

	while (current_record)
	{
	   new_record = current_record->next;
	   delete current_record;
	   current_record = new_record;
	}

}



template <class X> void XTable<X>::Init()
{
    current_record = NULL;
    new_record = NULL;
    counter = 0;
}

template <class X> bool XTable<X>::InitBuffer(int max_items)
{
    unsigned int it = 0;

    // Buffer already initialized
    if (first_record) return false;

    first_record = new Item<X>;
    if (!first_record) return false;

    current_record = first_record;

    do
    {
        new_record = new Item<X>;

        current_record->next = new_record;
        current_record = new_record;
        it++;
    } while ((new_record != NULL) && (it < max_items));

    if (it < max_items) return false;

    current_record->next = NULL;
    buffer_max_items = max_items;

    xitem = new XItem<X>;

    return true;
}

template <class X> bool XTable<X>::Insert(X item)
{

	current_record = first_record;

	if (current_record)
	{
		while ((current_record->next) && (current_record->enabled))
				current_record = current_record->next;

		// All available records already used
		if (!current_record->next) return false;
	}

	// Insert new item
	current_record->enabled = true;
	current_record->item = item;
    counter++;

    return true;
}

template <class X> X* XTable<X>::Select()
{
    if (!current_record->enabled) return NULL;
    return &(current_record->item);
}

template <class X> bool XTable<X>::Update(X item)
{
    if (!current_record) return false;

    current_record->item = item;
    return true;
}

template <class X> bool XTable<X>::Delete()
{
    if (!current_record) return false;

    current_record->enabled = false;
    counter--;
    return true;
}

template <class X> void XTable<X>::Clean()
{
    if (first_record)
    {
        current_record = first_record;

        do
        {
        	current_record->enabled = false;
            current_record=current_record->next;
        } while (current_record);
    }

    Init();
}

template <class X> bool XTable<X>::Top()
{
    if (!first_record) return false;

    current_record = first_record;
    if ((current_record && (!current_record->enabled))) return Next();

    return current_record->enabled;
}

template <class X> bool XTable<X>::Next()
{
    if ((!first_record) || (!current_record)) return false;

    current_record = current_record->next;
    if ((current_record && (!current_record->enabled))) Next();

    return (current_record);
}

template <class X> unsigned int XTable<X>::Counter()
{
	return counter;
}



// Status setting
// 0: 				BMK=0x42 first status markers = Begin MaRKer
// 1: 				buffer size (max number of items)
// <buffer_size>+2: EMK=0x45 second status markers = End MaRKer
//
// <------------ status --------------------------------> <-------- data ------------------>
// Marker Buf.Size <--- Status Buffer -----------> Marker <--- Parameter Buffer ----------->
// (0x42) (<size>) (x) (x) (x) (x) ... (x) (x) (x) (0x45) (<data>) ... (<data>) ... (<data>)
// BMK											   EMK
//
template <class X> bool XTable<X>::InitStorage(int start_location, int max_items) //uint8_t
{
    eeprom_max_items = -1;

    /// Validate buffer limits
    if ((max_items<=0) || (max_items > 255) || (start_location<0)) return false;

    /// Set EEPROM buffer startup pointer
    eeprom_header_begin = start_location;
    eeprom_max_items = max_items;
    eeprom_parameter_begin = start_location + eeprom_max_items + 4;

    if ((NextFreeAddressStorage()-1) > E2END) return false;

    if ( !((eeprom.read(eeprom_header_begin)==BMK) &&
         (eeprom.read(eeprom_header_begin+eeprom_max_items+2)==EMK) &&
         (eeprom.read(eeprom_header_begin+1) == eeprom_max_items)) )
    {
        eeprom.Fill(start_location, max_items*sizeof(XItem<X>) + max_items + 4, 0x00);

        /// Store status markers for initialized storage
        eeprom.write(start_location, BMK);
        eeprom.write(start_location+max_items+2, EMK);

        /// Store buffer size at first storage pointer
        eeprom.write(start_location+1, max_items);
    }

    return CheckStorage();
}


template <class X> int XTable<X>::GetTopAddressStorage()
{
    return top_parameter_ptr;
}


template <class X> int XTable<X>::NextFreeAddressStorage()
{
    if (eeprom_max_items<0) return -1;
    else return eeprom_max_items*sizeof(XItem<X>) + eeprom_max_items + 4 + eeprom_header_begin;
}


template <class X> bool XTable<X>::CheckStorage()
{
    if ((eeprom_max_items<=0) || (eeprom_max_items > 255) || (eeprom_header_begin<0)) return false;

    if ( (eeprom.read(eeprom_header_begin)==BMK) &&
         (eeprom.read(eeprom_header_begin+eeprom_max_items+2)==EMK) &&
         (eeprom.read(eeprom_header_begin+1) == eeprom_max_items) )
    {
        GetTopLocation();
        return true;
    }
    else return false;
}

template <class X> int XTable<X>::IncCurrentLocation(int curr_location)
{
    return ((curr_location+1-2)<(eeprom_header_begin + eeprom_max_items) ? curr_location+1 : eeprom_header_begin+2);
}

template  <class X> int XTable<X>::GetLocationFromStatus(int curr_status_ptr)
{
    return (curr_status_ptr-eeprom_header_begin-2)*sizeof(XItem<X>) + eeprom_parameter_begin;
}

template <class X> void XTable<X>::GetTopLocation()
{
    int current_location;
    int next_location;
    int tmp_location;

    current_location = eeprom_header_begin+2;
    next_location = current_location+1;

    while (eeprom.read(next_location) == eeprom.read(current_location)+1)
    {
        tmp_location = next_location;
        next_location = IncCurrentLocation(next_location);
        current_location = tmp_location;
    }

    top_status_ptr = current_location;
    top_parameter_ptr = GetLocationFromStatus(top_status_ptr);
}


template <class X> void XTable<X>::PutTopLocation()
{
    uint8_t current_value;

    current_value = eeprom.read(top_status_ptr);
    top_status_ptr = IncCurrentLocation(top_status_ptr);
    eeprom.write(top_status_ptr, current_value+1);
    top_parameter_ptr = GetLocationFromStatus(top_status_ptr);
}

template <class X> bool XTable<X>::SaveStorage()
{
    bool dataCheck;
    int curr_status_ptr;
    int curr_parameter_ptr;

    if (!CheckStorage()) return false;

    PutTopLocation();
    curr_status_ptr = top_status_ptr;
    curr_parameter_ptr = top_parameter_ptr;

    if (Top())
    do
    {
        xitem->item = current_record->item;
        xitem->enabled = current_record->enabled;

        eeprom.Write(curr_parameter_ptr, *xitem);
        curr_status_ptr = IncCurrentLocation(curr_status_ptr);
        curr_parameter_ptr = GetLocationFromStatus(curr_status_ptr);
    } while (Next());

    /// Update counter of available items
    eeprom.write(top_parameter_ptr-1, counter);

    /// Raw check of data within EEPROM
    dataCheck = CheckStorage();
    dataCheck &= (eeprom.read(top_parameter_ptr-1)==Counter());

    return dataCheck;
}


template <class X> bool XTable<X>::LoadStorage()
{
    uint8_t count;
    uint8_t idx;
    int curr_status_ptr;
    int curr_parameter_ptr;

    if (!CheckStorage()) return false;

    Clean();
    count = eeprom.read(top_parameter_ptr-1);

    curr_status_ptr = top_status_ptr;
    curr_parameter_ptr = top_parameter_ptr;

    idx = 0;
    while (idx < count)
    {
        xitem = eeprom.Read(curr_parameter_ptr);

        if (Insert(xitem->item))
			current_record->enabled = xitem->enabled;
        else return false;

        curr_status_ptr = IncCurrentLocation(curr_status_ptr);
		curr_parameter_ptr = GetLocationFromStatus(curr_status_ptr);

		idx++;
    }

    return true;
}

#endif /* XTable_H_ */
