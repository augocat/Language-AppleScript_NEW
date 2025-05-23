property type_list : {"JPEG", "TIFF", "GIF"}
property extension_list : {"jpg", "jpeg", "tif", "tiff", "gif"}
on open these_items
	repeat with i from 1 to the count of these_items
		set this_item to item i of these_items
		set the item_info to info for this_item
		if ((folder of the item_info is false) and Â
			(the file type of the item_info Â
				is in the type_list) or Â
			(the name extension of the item_info Â
				is in the extension_list)) then
			tell application "Preview" to open this_item
		end if
	end repeat
end open
