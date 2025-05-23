property master_coordinates : {}
on moving folder window for target_folder from start_coordinates
	if master_coordinates is {} then
		set master_coordinates to start_coordinates
		display dialog master_coordinates
	end if
	tell application "Finder"
		set bounds of window of target_folder to master_coordinates
	end tell
end moving folder window for
