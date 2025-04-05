property UTI_list : �
	{"public.jpeg", "public.tiff", "com.compuserve.gif"}

on open these_items
	repeat with i from 1 to the count of these_items
		set this_item to (item i of these_items)
		set the item_info to info for this_item
		if folder of the item_info is true then
			process_folder(this_item)
		else if (the type identifier of the item_info �
			is in the UTI_list) then
			process_item(this_item)
		end if
	end repeat
end open

on process_folder(this_folder)
	set these_items to list folder this_folder without invisibles
	repeat with i from 1 to the count of these_items
		set this_item to alias ((this_folder as text) �
			& (item i of these_items))
		set the item_info to info for this_item
		if folder of the item_info is true then
			process_folder(this_item)
		else if (the type identifier of the item_info �
			is in the UTI_list) then
			process_item(this_item)
		end if
	end repeat
end process_folder

on process_item(this_item)
	tell application "Preview" to open this_item
end process_item
