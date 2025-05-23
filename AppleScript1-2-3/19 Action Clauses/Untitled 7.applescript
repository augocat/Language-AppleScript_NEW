tell application "TextEdit"
	tell document 1
		get every word Â
			where it is equal to "carpenter"
	end tell
end tell
--> Returns: {"carpenter", "Carpenter"}
