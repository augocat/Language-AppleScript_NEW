on open these_items
	repeat with i from 1 to the count of these_items
		set this_item to item i of these_items
		set the item_info to info for this_item
		if folder of the item_info is true then
			process_folder(this_item)
		end if
	end repeat
end open

on process_folder(this_item)
	-- this_item is an alias reference to a folder
	-- FOLDER PROCESSING STATEMENTS GO HERE
	display dialog this_item as string
end process_folder
