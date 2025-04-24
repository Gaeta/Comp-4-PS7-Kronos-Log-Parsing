# PS7: Kronos Log Parsing

## Contact  
**Name:** Donald Gaeta  
**Section:** 202  

## Time to Complete  
Total: 3 hours  
- 2 Hours for implementation
- 1 Hour for testing and debugging

## Description
This project parses Kronos InTouch device logs to analyze boot-up sequences. The program reads an input log file and outputs a report listing each boot attempt, identifying whether it succeeded or failed, and calculating the boot time in milliseconds using timestamps and Boost's date-time library. The output also includes the total number of lines scanned and the number of boots initiated/completed.

### Features
- Parses boot start and completion log entries using regular expressions.
- Tracks line numbers and timestamps for easier debugging and traceability.
- Detects incomplete boots and reports failures when success markers are missing or out of order.
- Computes boot time in milliseconds using Boost date-time.
- Outputs a clean report with formatting that mimics the provided sample report.
- Includes extra credit: outputs a summary header before the detailed log.

### Approach
The program reads the log line by line, using regex to detect startup (`server started`) and successful boot completion (`Started SelectChannelConnector`) lines. It maintains a state (`bootStarted`) to ensure proper pairing of start and end events. If a new start is detected before a completion, the boot is marked as failed. After parsing, a report is written with total boots, successful completions, and timing information.

### Regex
- Start: `std::regex start("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}): \\(log\\.c\\.166\\) server started ");`
    This captures lines like 2025-04-21 14:23:55: (log.c.166) server started, indicating boot initiation.

- End: `std::regex end("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3}):INFO:oejs\\.AbstractConnector:Started SelectChannelConnector@0\\.0\\.0\\.0:9080");`
    This captures successful boot completions marked by `oejs.AbstractConnector`.


### Issues
- The program as of right now has no issues. I Initially struggled with matching timestamps using regex due to precision and whitespace handling.

### Extra Credit
- Summary header included in output report. (Only extra credit feature implemented)

## Acknowledgements
- **Instructor/TA**: Provided clarification on Discord  
- **SFML Documentation**: Referenced for rendering, textures, and input handling  
- **StackOverflow**: Used for various C++ issues and regex troubleshooting