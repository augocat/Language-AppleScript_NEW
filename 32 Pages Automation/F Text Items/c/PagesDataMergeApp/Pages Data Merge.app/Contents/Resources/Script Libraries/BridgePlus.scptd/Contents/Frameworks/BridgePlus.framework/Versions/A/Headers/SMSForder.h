//
//  SMSForder.h
//  BridgePlus
//
//  v1.3.2 Copyright (c) 2013-15 Shane Stanley.
//


/*
AppleScriptObjC in El Capitan handles the automatic conversion of text, numbers, booleans, lists, records, dates, and files to and from their Cocoa counterparts. However, before OS X 10.11 there was no conversion of dates and files, and there was also a loss of precision when converting floating-point Cocoa numbers to reals. This framework provides these extra conversions and precision with reals for scripts that also need to run on earlier versions of the OS. 
 
 It also provides trigonometry functions, several text-, list- and file-handling routines, methods for controlling keyboard input, and several other methods for users of any recent version of OS X.
 
Some of the facilities are based on those of ASObjC Runner and ASObjCExtras.framework, but to avoid potential clashes the SMSFord class has been replaced by the SMSForder class.

You can use the framework directly by putting it in ~/Library/Frameworks/ or /Library/Frameworks/, but preferably bundled within the BridgePlus.scpt library, which will load it when one of its commands is called.

Most methods will return missing value where there is an error, and if they have an error parameter the returned error will have a description in localizedError:.

You can use and distribute this framework free of charge, on its own or within BridgePlus.scptd, but it must include this header file. There are no guarantees or warranties whatsoever. Use entirely at your own risk. Feedback welcome to <sstanley@myriad-com.com.au>.
*/

    // Changes in v1.1.1: Bug fixes and the four Offset vs Range methods.
    // Changes in v1.2.0: Falls back to system bridging if running under OS X 10.11. Also includes many new methods, as marked.
    // Changes in v1.3.0: See new methods, as marked. Misc section has been rearranged, with separate group of URL and File methods.
    // Changes in v1.3.1: Bug fix for itemsIn:recursive:asPaths: method; was returning just files.
    // Changes in v1.3.2: Bug fix for intermittent crashes in keyboard input source methods.

// Further documentation: <http://www.macosxautomation.com/applescript/apps/BridgePlus_Manual/Index.html>

#import <Cocoa/Cocoa.h>


@interface SMSForder : NSObject

 
/////////////////////////////////////////////
#pragma mark House-keeping methods
/////////////////////////////////////////////

    // Returns the version of the framework. Typical use: current application's SMSForder's frameworkVersion()
    // If you are using the framework embedded in the BridgePlus.scpt script library, you can use the library's 'framework version' command instead.
+ (NSString *)frameworkVersion;

    // **** New in v1.2.0 **** //
    // Returns the date this version was compiled.
+ (NSString *)frameworkDate;


/////////////////////////////////////////////
#pragma mark Regular Expression methods
////////////////////////////////////////////

// **** New in v1.2.0 **** //

//The pattern syntax is that specified by ICU, described at http://userguide.icu-project.org/strings/regexp.

// The optionStrings parameter should be a string containing any or all of the following letters:
// i    Makes the search case insensitive
// x    Allows white space and #comments in the pattern
// s    Makes the "." character match a line terminator
// m    Makes "^" and "$" match the start/end of every line, not just the whole string
// w    Makes \b match word boundaries as described in Unicode UAX 29, rather than traditional regular expression behavior

// The format of a matchRecord dictionary is: {captureGroup:#, foundString:"found string", foundRange:{location:n, length:nn}}. For non-existent capture groups or capture groups that do not participate in a particular match, the foundString will be missing value, with a foundRange of {location:NSNotFound, length:0}.

// Returns the first matching string found. If none found, returns missing value.
+ (NSString *)findFirstMatch:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString;

// Returns the first match record found. If none found, returns missing value.
+ (NSDictionary *)findFirstMatchRecord:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString;

// Returns an array of the matching strings found. If none found, returns an empty array.
+ (NSArray *)findMatches:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString;

// Returns an array of the match records found. If none found, returns an empty array.
+ (NSArray *)findMatchRecords:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString;

// Returns an array for each match, sorted in your specified capture group order. If you specify non-existent capture groups or capture groups that do not participate in a particular match, they will be represented by missing value. If no matches are found, the overall result will be missing value.
+ (NSArray *)findMatches:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString captureGroups:(NSArray *)arrayOfIntegers;

// Returns an array of match records for each match, sorted in your specified capture group order. If no matches are found, the overall result will be missing value.
+ (NSArray *)findMatchRecords:(NSString *)regexPattern inString:(NSString *)searchString options:(NSString *)optionsString captureGroups:(NSArray *)arrayOfIntegers;


/////////////////////////////////////////////
#pragma mark String manipulation methods
////////////////////////////////////////////

    // Supply the format string you wish to use to convert the strings to NSDates. For example: "yyyy-MM-dd".
    // See http://unicode.org/reports/tr35/tr35-31.html#Date_Format_Patterns for format rules.
+ (NSArray *)datesFromStrings:(NSArray *)arrayOfStrings format:(NSString *)formatString;

    // Supply the format string you wish to use to convert the dates to strings. For example: "yyyy-MM-dd". The dates can be AS dates or NSDates.
    // See http://unicode.org/reports/tr35/tr35-31.html#Date_Format_Patterns for format rules.
+ (NSArray *)stringsFromDates:(NSArray *)arrayOfStrings format:(NSString *)formatString;

    // Converts tab-separated values to a list of lists
+ (NSArray *)arrayFromTSV:(NSString *)aString;

    // Converts comma-separated values to a list of lists. The commaIs parameter defines (single) character used
+ (NSArray *)arrayFromCSV:(NSString *)aString commaIs:(NSString *)commaString;

// The following methods modify a string or list of strings, returning a new string or list of strings accordingly. If a conversion can't be done, missing value will be returned for the relevant string.

    // Apply an ICU transform. See http://userguide.icu-project.org/transforms
+ (id)transformedFrom:(id)listOrString ICUTransform:(NSString *)transformName inverse:(BOOL)invertFlag;

    // Encodes the five reserved XML characters only: > < & " '
+ (id)encodedXMLFrom:(id)listOrString;

    // Decode the five reserved XML characters only > < & " '
+ (id)unencodedForXMLFrom:(id)listOrString;

    // Encodes characters outside ASCII 32-126 in decimal form (&#DD;), for use in HTML
+ (id)encodedDecimalFrom:(id)listOrString;

    // Decodes characters that appear in decimal form (&#DD;) or hexadecimal form (&#xHHHH;), as used in XML and HTML
+ (id)decodedDecimalFrom:(id)listOrString;

    // Encodes characters outside ASCII 32-126 in hexadecimal form (&#xHHHH;)
+ (id)encodedHexFrom:(id)listOrString;

    // Calculates the MD5 hash
+ (id)MD5From:(id)listOrString;

    // Converts straight quote marks into typographer's quote marks
+ (id)smartQuotedFrom:(id)listOrString;

    // Converts typographer's quote marks into straight quote marks
+ (id)unsmartQuotedFrom:(id)listOrString;

    // Converts runs of more than one space to a single space character, and trims spaces from the beginning and end of paragraphs.
+ (id)cleanSpacedFrom:(id)listOrString;

    // Deletes any paragraphs that are empty or contain only spaces and/or tabs
+ (id)emptyLineFreeFrom:(id)listOrString;


/////////////////////////////////////////////
#pragma mark Substring extraction methods
/////////////////////////////////////////////

// These methods parse a string into an array of substrings.
// The localized versions might return different results, depending on your locale.
 
+ (NSArray *)charactersOfString:(NSString *)aString; // "character" means "composed character sequence", as in AppleScript

+ (NSArray *)wordsOfString:(NSString *)aString; // ignore localization

+ (NSArray *)localizedWordsOfString:(NSString *)aString;

+ (NSArray *)sentencesOfString:(NSString *)aString; // ignore localization

+ (NSArray *)localizedSentencesOfString:(NSString *)aString;

+ (NSArray *)paragraphsOfString:(NSString *)aString;

    // lines is like paragraph but also includes Unicode line-break character
+ (NSArray *)linesOfString:(NSString *)aString;

    // **** New in v1.2.0 **** //
// Returns an array of all matching substrings. Anchored and backwards search options don't make sense here.
+ (NSArray *)stringsOfString:(NSString *)toFind inString:(NSString *)aString options:(NSStringCompareOptions)compareOptions;

// **** New in v1.2.0 **** //
// Locale-sensitive version of the previous method.
+ (NSArray *)stringsOfString:(NSString *)toFind inString:(NSString *)aString options:(NSStringCompareOptions)compareOptions locale:(NSLocale *)aLocale;


/////////////////////////////////////////////
#pragma mark Substring range methods
/////////////////////////////////////////////

// These methods parse a string into an array of the ranges of the substrings. The ranges are in the form of NSRanges, which convert to AppleScript records of the form {location:5, length:3}, where location is the zero-based offset, and length is the length of the substring.

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfCharactersOfString:(NSString *)aString; // "character" means "composed character sequence", as in AppleScript

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfWordsOfString:(NSString *)aString; // ignore localization

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfLocalizedWordsOfString:(NSString *)aString;

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfSentencesOfString:(NSString *)aString; // ignore localization

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfLocalizedSentencesOfString:(NSString *)aString;

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfParagraphsOfString:(NSString *)aString;

    // **** New in v1.2.0 **** //
+ (NSArray *)rangesOfLinesOfString:(NSString *)aString;

    // **** New in v1.2.0 **** //
    // Returns an array of NSRanges, representing the range of every instance of the search string. Anchored and backwards search options don't make sense here.
+ (NSArray *)rangesOfString:(NSString *)findString inString:(NSString *)aString options:(NSStringCompareOptions)options;

    // **** New in v1.2.0 **** //
    // Locale-sensitive version of the previous method.
+ (NSArray *)rangesOfString:(NSString *)findString inString:(NSString *)aString options:(NSStringCompareOptions)options locale:(NSLocale *)locale;


/////////////////////////////////////////////
#pragma mark Deprecated substring range methods
/////////////////////////////////////////////

// **** Deprecated in v1.2.0 **** //
// These methods all have equivalents above that return arrays of NSRanges, whereas these return the same values as arrays of arrays. So {{5,3}, {12,3},...}, instead of {{location:5, length:3}, {location:12, length:3},...}. These continue to work, but the above methods are preferred.

+ (NSArray *)characterRangesOfString:(NSString *)aString;

+ (NSArray *)wordRangesOfString:(NSString *)aString;

+ (NSArray *)localizedWordRangesOfString:(NSString *)aString;

+ (NSArray *)sentenceRangesOfString:(NSString *)aString;

+ (NSArray *)localizedSentenceRangesOfString:(NSString *)aString;

+ (NSArray *)paragraphRangesOfString:(NSString *)aString;

+ (NSArray *)lineRangesOfString:(NSString *)aString;


/////////////////////////////////////////////
#pragma mark Substring counting methods
/////////////////////////////////////////////

// These methods return the number of substrings in the string.

+ (NSUInteger)characterCountOfString:(NSString *)aString; // "character" means "composed character sequence", as in AppleScript

+ (NSUInteger)wordCountOfString:(NSString *)aString;

+ (NSUInteger)localizedWordCountOfString:(NSString *)aString;

+ (NSUInteger)sentenceCountOfString:(NSString *)aString;

+ (NSUInteger)localizedSentenceCountOfString:(NSString *)aString;

+ (NSUInteger)paragraphCountOfString:(NSString *)aString;

+ (NSUInteger)lineCountOfString:(NSString *)aString;


/////////////////////////////////////////////
#pragma mark Offset vs Range methods
////////////////////////////////////////////

// **** New in v1.1.1 **** //

// These methods can be used to convert between AppleScript character indexes or offsets (which are based on composed character sequences) and NSRange values (which are based 16-bit unichar values). Range location and character index only differ when the text contains code points ouside Unicode's Basic Multilingual Plane.

    // Convert a character index from AppleScript to a Cocoa location or NSRange
+ (NSUInteger)locationOfCharacterAt:(NSNumber *)offset inString:(NSString *)aString;
+ (NSRange)rangeOfCharacterAt:(NSNumber *)offset inString:(NSString *)aString;

    // Convert a Cocoa location or NSRange to an AppleScript index
+ (NSUInteger)offsetOfLocation:(NSNumber *)location inString:(NSString *)aString;
    // Here, offsets is a list of two values, being the first and last character offsets
+ (NSArray *)offsetsOfRange:(NSRange)range inString:(NSString *)aString;


/////////////////////////////////////////////
#pragma mark List manipulation methods
////////////////////////////////////////////

// These methods (mostly) return an array.

    // Assumes the input is a list of lists, and the pad item will be used to pad out any sublists that are shorter than the longest
+ (NSArray *)subarraysIn:(NSArray *)listOrArray paddedWith:(id)pad error:(NSError *__autoreleasing *)outError;

    // Works on a list of lists, each containing the same number of entries. The result will also be a list of lists, where the first list will consist of the first item of each of the original lists, and so on. Calling it a second time effectively returns the list to its original value
+ (NSArray *)colsToRowsIn:(NSArray *)listOrArray error:(NSError *__autoreleasing *)outError;

    // Flattens a list of lists to a single list: {{1, 2}, {3, 4}} --> {1, 2, 3, 4}. Flattens one level only.
+ (NSArray *)arrayByFlattening:(NSArray *)listOrArray;

    // Flattens a list to a single list: {1, 2, {3, {4, 5}}} --> {1, 2, 3, 4, 5}. Flattens all levels
+ (NSArray *)arrayByFullyFlattening:(NSArray *)listOrArray;

    // Breaks list into subarrays of aNumber items
+ (NSArray *)subarraysFrom:(NSArray *)listOrArray groupedBy:(NSNumber *)aNumber error:(NSError *__autoreleasing *)outError;

    // Assumes the array is a list of lists. The insertion list must have the same number of elements, and the first element will be inserted into the main list's first list, the second into the main list's second list, and so on. Where it is inserted is determined by the (zero-based) 'insertedAtIndex' parameter.
+ (NSArray *)subarraysIn:(NSArray *)listOrArray withItems:(NSArray *)insertArray insertedAtIndex:(NSInteger)atIndex error:(NSError *__autoreleasing *)outError;

    // Inserts a list of items as separate items into the list. Index is zero-based.
+ (NSArray *)arrayByInsertingItems:(id)listOrArrayToInsert inArray:(NSArray *)listOrArray atIndex:(NSInteger)atIndex error:(NSError *__autoreleasing *)outError;

    // Does what it says. Indexes are zero-based.
+ (NSArray *)arrayByMovingItemAt:(NSInteger)fromIndex toIndex:(NSInteger)toIndex inArray:(NSArray *)listOrArray error:(NSError *__autoreleasing *)outError;

    // Delete any blank items. Blanks are missing value, empty strings, empty lists, and lists consisiting only of the above.
+ (NSArray *)arrayByDeletingBlanksIn:(NSArray *)listOrArray;

    // Trim any blank items from the trailing end of the list. Blanks are missing value, empty strings, empty lists, and lists consisting only of the above.
+ (NSArray *)arrayByTrimmingTrailingBlanksFrom:(NSArray *)listOrArray;

    // Trim any blank items from both ends of the list. Blanks are missing value, empty strings, empty lists, and lists consisting only of the above.
+ (NSArray *)arrayByTrimmingBlanksFrom:(NSArray *)listOrArray;

    // Instances of 'missing value' will be replaced with whatever you pass to withItem:
+ (NSArray *)arrayByReplacingNullsIn:(NSArray *)listOrArray withItem:(id)anItem;

    // Pattern should be a string where every instance of %@ will be replaced by a number. So a pattern of "label%@", a startNumber of 3, an endNumber of 1  and minDigits 3 will return {"label003", "label002", "label001"}
+ (NSArray *)arrayWithPattern:(NSString *)patternString startNumber:(NSNumber *)startNum endNumber:(NSNumber *)endNum minDigits:(NSNumber *)minDigits;

    // Returns an array of {sum, max, min} of the list.
+ (NSArray *)sumMaxMinOf:(NSArray *)listOrArray error:(NSError *__autoreleasing *)outError;

    // Sort a lists of lists based on indexes of the sublists. So if the (zero-based) indexes are {3, 2}, the list will be sorted based on the value of the fourth item of the sublists, and in cases of equality, then on the third. The ascending argument should be a list of booleans, matching the indexes; if it has fewer entries, the last entry will be used for subsequent sort order. Pass an empty list to use true throughout. The sortTypes argument should be a list of strings consisting of the comparison selectors to use: "compare:", "localizedCompare:", "caseInsensitiveCompare:", "localizedCaseInsensitiveCompare:" and "localizedStandardCompare:". Pass an empty list to use "compare:" throughout.
+ (NSArray *)subarraysIn:(NSArray *)listOrArray sortedByIndexes:(NSArray *)theIndexes ascending:(NSArray *)orderBooleans sortTypes:(NSArray *)sortSelctorStrings error:(NSError *__autoreleasing *)outError;

    // As above, but you can also pass a list of key strings to be used for the sort. Pass an empty list to use "self" throughout, which is what the above method uses. For example, if you pass {"length"}, the sorting will be done on the basis of the length. The values being sorted must support the key or an error will be thrown.
+ (NSArray *)subarraysIn:(NSArray *)listOrArray sortedByIndexes:(NSArray *)theIndexes ascending:(NSArray *)orderBooleans sortTypes:(NSArray *)sortSelctorStrings sortKeys:(NSArray *)sortKeys error:(NSError *__autoreleasing *)outError;

    // Concatenate two text items into one. Provide a list of the (zero-based) indexes of the items to merge; they will be joined using the separator in the order provided, and appear at the first of the indexes. Empty strings will be ignored.
+ (NSArray *)arrayByMergingTextAtIndexes:(NSArray *)mergingIndexes inArray:(NSArray *)listOrArray inserting:(NSString *)separatorString error:(NSError *__autoreleasing *)outError;

    // Returns list of indexes where item is found; inverting true returns indexes where the item is not found. Indexes are zero-based.
+ (NSArray *)indexesOfItem:(id)theItem inArray:(NSArray *)listOrArray inverting:(BOOL)invertFlag;

    // Returns list of indexes where any of the items in the list are found; inverting true returns indexes where the items are not found.  Indexes are zero-based.
+ (NSArray *)indexesOfItems:(NSArray *)listOfItems inArray:(NSArray *)listOrArray inverting:(BOOL)invertFlag;

    // Assumes the array is a list of lists, and that each list has the same number of items as the list of labels. The result will be an array of records/dictionaries that use the supplied labels in order.
+ (NSArray *)subarraysIn:(NSArray *)listOrArray asDictionariesUsingLabels:(NSArray *)theLabels error:(NSError *__autoreleasing *)outError;

    // Pass a list of records/dictionaries and a list of labels, and a list of lists will be returned, with the order of the values in each sublist matching the order of the labels. If an empty list is passed for usingKeys, the keys of the first item will be used, sorted in case-insensitive alphabetical order, and these keys will be listed as strings in outKeys.
+ (NSArray *)subarraysFrom:(NSArray *)arrayOfDicts usingKeys:(NSArray *)theKeys outKeys:(NSArray *__autoreleasing *)outKeys error:(NSError *__autoreleasing *)outError;

    // ASObjC can't normally extract the values from an IndexSet; this method makes it possible
+ (NSArray *)arrayWithIndexSet:(NSIndexSet *)theIndexSet;

    // Increment each of the values in a list of integers by anInteger. Provide a negative value to decrement the values
+ (NSArray *)arrayByAddingInteger:(NSNumber *)anInteger inArray:(NSArray *)arrayOfIntegers;

    // Sorts a list using the sort algorithm you provide. The selector will be used as the sorting comparator.
    // 'stableSort' should be true for a stable sort.
    // The selector needs to take two parameters, which are the two values being compared. It should return 1 if the first value is the greater, -1 if it's the lesser, and 0 if they are the same. So you might pass something like: "compareThis:withThis:", and your script would then include a handler "on compareThis:x withThis:y".
    // For target, pass the constant me.

    // The calling of methods back-and-forth means this can be a pretty slow way to sort, especially if the objects are bridged.
+ (NSArray *)sortedArrayFrom:(NSArray *)listOrArray stableSort:(BOOL)stableSortFlag usingSelector:(SEL)selectorString target:(NSObject *)target;

    // **** New in v1.2.0 **** //
    // Pass a list of integers to build an index set.
+ (NSIndexSet *)indexSetWithArray:(NSArray *)listOrArray;

// **** New in v1.3.0 **** //
// Pass an array of items, and have them split into subarrays according to the provided key. The optional sortKeys are used to sort the objects within the subarrays; pass an empty list if you do not need them sorted. Items not responding to the key are grouped last.
+ (NSArray *)splitArray:(NSArray *)listOrArray byKey:(NSString *)splitKey sortKeys:(NSArray *)sortKeys;

// **** New in v1.3.0 **** //
// Pass an array of items, and have them sorted by the keys, in oder.
+ (NSArray *)sortedArrayFrom:(NSArray *)listOrArray byKeys:(NSArray *)sortKeys;

/////////////////////////////////////////////
#pragma mark Trigonometry methods
/////////////////////////////////////////////

// Pass a single number or a list of numbers. Results must be coerced. Angles are in radians, and errors are returned as missing value.

+ (id)tanValueOf:(id)listOrNumber;
+ (id)sinValueOf:(id)listOrNumber;
+ (id)cosValueOf:(id)listOrNumber;
+ (id)atanValueOf:(id)listOrNumber;
+ (id)asinValueOf:(id)listOrNumber;
+ (id)acosValueOf:(id)listOrNumber;
+ (id)tanhValueOf:(id)listOrNumber;
+ (id)sinhValueOf:(id)listOrNumber;
+ (id)coshValueOf:(id)listOrNumber;
+ (id)atanhValueOf:(id)listOrNumber;
+ (id)asinhValueOf:(id)listOrNumber;
+ (id)acoshValueOf:(id)listOrNumber;
+ (id)logValueOf:(id)listOrNumber;
+ (id)log10ValueOf:(id)listOrNumber;

 
/////////////////////////////////////////////
#pragma mark URL and File related methods
/////////////////////////////////////////////

    // Pass an alias, file, HFS path, POSIX path or NSURL for an image file, and receive back a dictionary/record of the metadata.
+ (NSDictionary *)metadataFromImage:(id)fileAliasOrPath error:(NSError *__autoreleasing *)outError;

    // Takes an alias, file, HFS path, POSIX path or NSURL and returns a dictionary/record. The labels can be found by looking up NSURL; the prefix "NSURL" and suffix "Key" are removed, and the initial character made lowercase.
+ (NSDictionary *)infoForFile:(id)fileAliasOrPath;

    // Takes an alias, file, HFS path, POSIX path or NSURL and returns a dictionary/record.
    // For files, the values are returned like this: {totalFileSize:94927, totalFileAllocatedSize:98304, fileAllocatedSize:98304, fileSize:94927}
    // The "total" values include metadata; "Allocated" means disk space used. Finder reports totalFileSize.
    // For directories and packages, only the total values are returned: {totalFileSize:271230605, totalFileAllocatedSize:286121984}.
+ (NSDictionary *)sizeInfoForFile:(id)fileAliasOrPath;

    // **** New in v1.2.0 **** //
    // Equivalent to calling getResourceValue:forKey:error: on a list or array of aliases, files, HFS paths, POSIX paths or NSURLs. Returns the results as an array.
+ (NSArray *)resourceValueForKey:(NSString *)resourceKey forURLsOrFiles:(NSArray *)urlsFilesOrPaths;

    // **** New in v1.2.0 **** //
    // Equivalent to calling resourceValuesForKeys:error: on a list or array of aliases, files, HFS paths, POSIX paths or NSURLs. Returns the results as an array of dictionaries.
    // **** Change in v1.3.0 **** //
    // Now always includes the value for NSURLPathKey.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forURLsOrFiles:(NSArray *)urlsFilesOrPaths;

// **** New in v1.3.0 **** //
// Enumerate the directory (passed as an alias, file, HFS path, POSIX path or NSURL), and return an array of either paths or NSURLs of the contained folders, files and packages.
+ (NSArray *)itemsIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden files and files inside packages.
+ (NSArray *)itemsIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// Enumerate the directory (passed as an alias, file, HFS path, POSIX path or NSURL), and return an array of either paths or NSURLs of the contained files and packages.
+ (NSArray *)filesIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden files and files inside packages.
+ (NSArray *)filesIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// Enumerate the directory (passed as an alias, file, HFS path, POSIX path or NSURL), and return an array of either paths or NSURLs of the contained folders.
+ (NSArray *)foldersIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden folders and folders inside packages.
+ (NSArray *)foldersIn:(id)urlFileOrPath recursive:(BOOL)recurseFlag asPaths:(BOOL)pathsFlag;

// **** New in v1.3.0 **** //
// Enumerate the directory (passed as an alias, file, HFS path, POSIX path or NSURL), and return the resource values for the requested keys of the items in it. Always includes the value for NSURLPathKey.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forItemsIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden files and files inside packages.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forItemsIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag;

// **** New in v1.3.0 **** //
// As above, but only return values for files and packages, not folders. Always includes the values for NSURLPathKey and NSURLIsPackageKey.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forFilesIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden files and files inside packages.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forFilesIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag;

// **** New in v1.3.0 **** //
// As above, but only return values for folders, not files and packages. Always includes the value for NSURLPathKey.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forFoldersIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag skipHidden:(BOOL)hiddenFlag skipInsidePackages:(BOOL)skipInPackagesFlag;

// **** New in v1.3.0 **** //
// As above, skipping hidden files and files inside packages.
+ (NSArray *)resourceValuesForKeys:(NSArray *)resourceKeys forFoldersIn:(NSString *)urlFolderOrPath recursive:(BOOL)recurseFlag;

// **** New in v1.3.0 **** //
// Copies item, with atomic replacement if replaceFlag is true and destination item already exists. Pass aliases, files, HFS paths, POSIX paths or NSURLs.
+ (BOOL)copyItemAt:(id)urlFileOrPath toItem:(id)destUrlFileOrPath replace:(BOOL)replaceFlag error:(NSError *__autoreleasing *)outError;

// **** New in v1.3.0 **** //
// Moves item, with atomic replacement if replaceFlag is true and destination item already exists. Pass aliases, files, HFS paths, POSIX paths or NSURLs.
+ (BOOL)moveItemAt:(id)urlFileOrPath toItem:(id)destUrlFileOrPath replace:(BOOL)replaceFlag error:(NSError *__autoreleasing *)outError;

    // **** New in v1.3.0 **** //
    // Pass an extension and get back the UTI.
+ (NSString *)UTIForExtension:(NSString *)extension;

// **** New in v1.3.0 **** //
// Conduct a Spotlight metadata search. The query string needs to be a valid Spotlight query, such as "kMDItemFSInvisible = YES". listOfFilesPathsURLsOrQueryScopeConstants can contain aliases, files, HFS paths, POSIX paths or NSURLs, as well as query scope constants such as 'current application's NSMetadataQueryLocalComputerScope'. Returns an array of POSIX paths, or missing value if there is an error.
+ (NSArray *)runSpotlightQuery:(NSString *)queryString inFolders:(NSArray *)listOfFilesPathsURLsOrQueryScopeConstants error:(NSError *__autoreleasing *)outError;

// **** New in v1.3.0 **** //
// As above, but allowing the use of placeholder strings in the query string. For example, a query string of "kMDItemFSCreationDate > %@" could be used with queryValues of {someDate}. Where queryValues should contain dates, both NSDates and AppleScript dates are accepted.
+ (NSArray *)runSpotlightQuery:(NSString *)queryString queryValues:(NSArray *)queryValues inFolders:(NSArray *)listOfFilesPathsURLsOrQueryScopeConstants error:(NSError *__autoreleasing *)outError;

// **** New in v1.3.0 **** //
// Returns the Spotlight metadata for a file, or missing value if there is a problem.
+ (NSDictionary *)spotlightDataFor:(id)filePathOrURL;

/////////////////////////////////////////////
#pragma mark Miscellaneous methods
/////////////////////////////////////////////

    // **** New in v1.2.0 **** //
    // This returns a record containing the entire path and *closed* value for a bezier, in a format suitable for use in Adobe Illustrator. After coercing to a record you can use it directly -- for example: "set properties of path item x to theRecord". The bezier should consist of a single unbroken path.
+ (NSAppleEventDescriptor *)bezierForAI:(NSBezierPath *)theBezier;

    // **** New in v1.2.0 **** //
    // This returns a record containing the entire path and *path type* value for a bezier, in a format suitable for use in Adobe InDesign. After coercing to a record you can use it directly -- for example: "set properties of path 1 of page item x to theRecord". The bezier shoul consist of a single unbroken path.
    // Because InDesign's vertical coordinates run from top to bottom, angles are rotated 180 degrees.
+ (NSAppleEventDescriptor *)bezierForID:(NSBezierPath *)theBezier;

    // **** New in v1.2.0 **** //
    // This returns a record with labels is_closed and path_points. The is_closed value is a boolean, and the path_points value is a list of lists containing either the {anchorX, anchorY} or {{anchorX, anchorY}, {leftX, leftY}, {rightX, rightY}} coordinates of the points of the path. This is the same value as is returned for entire path by the previous method.
+ (NSDictionary *)pathOfBezier:(NSBezierPath *)theBezier;

    // These are workarounds for some methods that can't be called directly via ASObjC.

    // **** New in v1.2.0 **** //
    // This provides access to the result of the -getLineDash:count:phase: method of NSBezierPath.
+ (NSArray *)lineDashCountAndPhaseOfBezier:(NSBezierPath *)theBezier;

    // **** New in v1.2.0 **** //
    // This provides access to the result of the -getComponents method of NSColor.
+ (NSArray *)componentsOfColor:(NSColor *)theColor;

    // **** New in v1.3.0 **** //
    // Use to force screen updates and/or keep an app responsive without the spinning cursor. Calls nextEventMatchingMask:untilDate:inMode:dequeue: and sendEvent: to handle any pending events before continuing.
+ (void)fordEvent;

    // **** New in v1.3.0 **** //
    // Retrieves a generic keychain password. Searches all keychains, and returns the first match it finds.
    // Returns missing value if not found; check localizedDescription of error for explanation.
+ (NSString *)passForGenericItem:(NSString *)itemName account:(NSString *)theAccount error:(NSError *__autoreleasing *)outError;

    // **** New in v1.3.0 **** //
    // Retrieves a generic keychain password from the keychain at the specified path. Returns the first match.
    // Returns missing value if not found; check localizedDescription of error for explanation.
+ (NSString *)passForGenericItem:(NSString *)itemName account:(NSString *)theAccount keychainPath:(NSString *)keychainPath error:(NSError *__autoreleasing *)outError;

    // **** New in v1.3.0 **** //
    // Retrieves an Internet keychain password. Searches all keychains, and returns the first match it finds.
    // The server, path and port parameters are optional; you can provide missing value for any and all of them.
    // For a URL like "http:/www.apple.com:80/blah/blah", the server is "www.apple.com", the port is 80, and the path is "/blah/blah"
    // Returns missing value if not found; check localizedDescription of error for explanation.
+ (NSString *)passForInternetItem:(NSString *)itemName account:(NSString *)theAccount server:(NSString *)theServer path:(NSString *)thePath port:(NSNumber *)thePort error:(NSError *__autoreleasing *)outError;

    // **** New in v1.3.0 **** //
    // Retrieves an Internet keychain password from the keychain at the specified path. Returns the first match.
    // The server, path and port parameters are optional; you can provide missing value for any and all of them.
    // For a URL like "http:/www.apple.com:80/blah/blah", the server is "www.apple.com", the port is 80, and the path is "/blah/blah"
    // Returns missing value if not found; check localizedDescription of error for explanation.
+ (NSString *)passForInternetItem:(NSString *)itemName account:(NSString *)theAccount server:(NSString *)theServer path:(NSString *)thePath port:(NSNumber *)thePort keychainPath:(NSString *)keychainPath error:(NSError *__autoreleasing *)outError;

// **** New in v1.3.0 **** //
// Pass an AS date or NSDate. Returns an array of {era, year, month, day} in the current calendar.
+ (NSArray *)dateValuesFrom:(id)ASOrNSDate;

// **** New in v1.3.0 **** //
// Pass an AS date or NSDate. Returns an array of {era, year for week of year, week of year, weekday} in the current calendar.
+ (NSArray *)extraDateValuesFrom:(id)ASOrNSDate;

// **** New in v1.3.0 **** //
// Pass an AS date or NSDate. Returns an array of {hour, minutes, seconds, milliseconds} in the current calendar.
+ (NSArray *)timeValuesFrom:(id)ASOrNSDate;



/////////////////////////////////////////////
#pragma mark Keyboard input source methods
/////////////////////////////////////////////

    // **** New in v1.2.0 **** //
    // Lists the IDs of the enabled input sources.
+ (NSArray *)availableInputSourceIDs;

    // **** New in v1.2.0 **** //
    // Lists the IDs of all installed input sources.
+ (NSArray *)allAvailableInputSourceIDs;

    // **** New in v1.2.0 **** //
    // ID of the current keyboard input source.
+ (NSString *)currentKeyboardInputSourceID;

    // **** New in v1.2.0 **** //
    // If the current keyboard input source is a keyboard layout, returns its ID. If the current keyboard input source is an input method or mode, returns the ID of the keyboard layout used by that input method or mode.
+ (NSString *)currentKeyboardLayoutInputSourceID;

    // **** New in v1.2.0 **** //
    // Changes the current Input Source.
+ (BOOL)changeInputSourceTo:(NSString *)inputSourceID;


/////////////////////////////////////////////
#pragma mark AppleScript to Cocoa conversions
/////////////////////////////////////////////
 
// These methods are for converting from AppleScript objects to Cocoa objects. Conversion is recursive through any contained records and lists.

    // Converts any contained AS dates to NSDates and any aliases, files or bookmarks to NSURLs.
    // Typical use: set theArray to current application's SMSForder's Cocoaify:listOfDates
    // Bridge does the conversion under 10.11 and later.
+ (id)CocoaifyFrom:(id)anASItem;

    // As above, but you can control which classes get converted. The string you pass can be comma- or space-delimited.
    // If it contains the word dates, AS dates will be converted to NSDates.
    // If it contains the word data, AS data will be converted to NSData.
    // If it contains the word files, files and aliases will be converted to NSURLs.
    // So this: set theArray to current application's SMSForder's Cocoaify:listOfDates forTypes:"dates"
    // is the same as: set theArray to current application's SMSForder's Cocoaify:listOfDates
+ (id)CocoaifyFrom:(id)anASItem forTypes:(NSString *)typesString;


/////////////////////////////////////////////
#pragma mark Cocoa to AppleScript conversions
/////////////////////////////////////////////
 
// These methods are for converting from Cocoa objects to AppleScript objects. They also perform the conversion of any floating-point numbers to reals, to work around the imprecision of the built-in conversion. Conversion is recursive through any contained records and lists.

    // Converts any NSDates to AS dates, NSURLs to files («class furl»), and any floating-point numbers to reals, to work around the imprecision of the built-in conversion. Result must still be coerced.
    // Typical use: set theList to current application's SMSForder's ASifyFrom:anArray as list
    // Bridge does the conversion under 10.11 and later.
+ (id)ASifyFrom:(id)anItem;

    // As above, but returns the result in a single-item list. Use this when unsure of the class of the result, and extract the first item from the result coerced to a list. Works around coercion problem.
    // Typical use: set theThing to item 1 of (current application's SMSForder's ASifyFrom:anArray as list)
    // Bridge does the conversion under 10.11 and later.
+ (id)ASifyInListFrom:(id)anItem;

    // Similar to ASIfyFrom:, but you can control which classes get converted. The string you pass can be comma- or space-delimited.
    // If it contains the word reals, floating-point numbers will be converted to reals.
    // If it contains the word dates, NSDates will be converted to AS dates.
    // If it contains the word data, NSData will be converted to AS data.
    // If it contains the word files, NSURLs will be converted to AS files («class furl»).
    // So this: set theList to (current application's SMSForder's ASifyFrom:anArray forTypes:"files, dates, reals") as list
    // is the same as: set theList to current application's SMSForder's ASifyFrom:aList as list
+ (id)ASifyFrom:(id)anItem forTypes:(NSString *)typesString;

    // As above, but returns the result in a single-item list.See ASIfyInList.
    // Typical use: set theData to item 1 of ((current application's SMSForder's ASifyFrom:anNSData forTypes:"data") as list)
+ (id)ASifyInListFrom:(id)anItem forTypes:(NSString *)typesString;


/////////////////////////////////////////////
#pragma mark Specialist conversion methods
/////////////////////////////////////////////

    // Pass an alias, file, HFS path or POSIX path, and an NSURL will be returned
+ (NSURL *)URLFrom:(id)aliasFileOrPath;

// **** New in v1.3.0 **** //
// Pass a list or array of aliases, files, HFS paths or POSIX paths, and an array of NSURLs will be returned.
+ (NSArray *)URLsFrom:(NSArray *)aliasesFilesOrPaths;

// Pass an NSURL, and a file («class  furl») will be returned. You will need to coerce the result with "as «class furl»"
+ (NSAppleEventDescriptor *)fileFromURL:(NSURL *)theUrl;

    // Pass an NSURL, and the HFS path is returned. Directories will have a trailing colon; packages will not
+ (NSString *)HFSPathFromURL:(NSURL *)theUrl;

    // As above, except you specify whether package paths have colons appended
+ (NSString *)HFSPathFromURL:(NSURL *)theUrl colonForPackages:(BOOL)colonForPackagesFlag;


@end


