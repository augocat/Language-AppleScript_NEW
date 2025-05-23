property UTI_list : Â
	{"public.jpeg", "public.tiff", "com.compuserve.gif"}
on open these_items
	repeat with i from 1 to the count of these_items
		set this_item to item i of these_items
		set the item_info to info for this_item
		if (folder of the item_info is false) and Â
			(the type identifier of the item_info Â
				is in the UTI_list) then
			tell application "Preview" to open this_item
		end if
	end repeat
end open
