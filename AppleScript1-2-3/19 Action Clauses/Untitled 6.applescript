tell application "TextEdit"
	tell document 1
		considering case
			word 1 is equal to word 2
		end considering
	end tell
end tell
--> Returns: false
