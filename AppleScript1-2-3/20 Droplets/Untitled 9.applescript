property UTI_list : Â
	{"public.jpeg", "public.tiff", "com.compuserve.gif", "public.png", "com.adobe.pdf"}
property post_alert : true

on run
	repeat
		display dialog ("My File Processing Droplet") Â
			& return & return Â
			& ("Post User Alert: ") & (post_alert as text) Â
			buttons {"Cancel", "Set Prefs", "Done"} Â
			default button 3
		if the button returned of the result is "Set Prefs" then
			display dialog Â
				("Should this droplet post an alert ") Â
					& ("when items it can't handle ") Â
				& ("are dropped onto it?") Â
				& return & return Â
				& ("Current Status: ") Â
				& (post_alert as text) Â
				buttons {"Cancel", "False", "True"}
			if the button returned of the result is "False" then
				set post_alert to false
			else
				set post_alert to true
			end if
		else
			return "done"
		end if
	end repeat
end run

on reopen
	run
end reopen

on open these_items
	repeat with i from 1 to the count of these_items
		set this_item to item i of these_items
		set the item_info to info for this_item
		--display dialog UTI_list as text
		if (folder of the item_info is false) and Â
			(the type identifier of the item_info Â
				is in the UTI_list) then
			process_item(this_item)
		else if post_alert is true then
			set old_delimiters Â
				to AppleScript's text item delimiters
			set AppleScript's text item delimiters to {", "}
			set the display_list to UTI_list as string
			set AppleScript's text item delimiters Â
				to old_delimiters
			tell application Â
				(path to frontmost application as string)
				beep
				display dialog Â
					("This droplet only processes ") Â
						& ("files of type:") Â
					& return & return Â
					& display_list Â
					giving up after 15 Â
					buttons {"OK"} default button "OK"
			end tell
		end if
	end repeat
end open

on process_item(this_item)
	tell application "Preview" to open this_item
end process_item
