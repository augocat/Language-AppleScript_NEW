tell application "TextEdit"
	tell document 1
		get every word �
			where it is equal to "carpenter"
	end tell
end tell
--> Returns: {"carpenter", "Carpenter"}
