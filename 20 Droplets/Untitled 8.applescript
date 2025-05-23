on run
	report("Run handler")
end run

on open my_items
	report("Open handler")
end open

on reopen
	report("Reopen handler")
end reopen

on report(message)
	display dialog message buttons {"OK"} default button "OK"
end report
