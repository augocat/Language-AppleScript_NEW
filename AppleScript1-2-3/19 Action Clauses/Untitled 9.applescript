tell application "TextEdit"
	tell document 1
		considering case
			get every word Â
				where it is equal to "carpenter"
		end considering
	end tell
end tell
--> Returns: {"carpenter", "Carpenter"} WRONG!
