tell application "TextEdit"
	tell document 1
		ignoring case
			get every word �
				where it is equal to "carpenter"
		end ignoring
	end tell
end tell
--> Returns: {"carpenter", "Carpenter"}
