# Event Tracing Experiments
Windows Event Tracing Experiments

## Rolling Dice
This is a little example console application.
It rolls 2x W6 dice every second, prints the result on the console output and traces the result.


## Windows Performance Recorder
To record a event trace file you can use the [Windows Performance Recorder](https://docs.microsoft.com/en-us/windows-hardware/test/wpt/windows-performance-recorder).

From an admin command prompt run:
```PS
wpr -start .\diceprofile.wprp -filemode
```
to start the tracing.

Then run the Rolling Dice application.

To stop the tracing and write the trace file run: (admin command prompt)
```PS
wpr -stop trace.etl
```
This will write the file `trace.etl`.
You can open the file, for example, with the [Windows Performance Analyzer](https://docs.microsoft.com/en-us/windows-hardware/test/wpt/windows-performance-analyzer).


## License
The these experimental tools are available freely under the terms of the Apache License, V.2

> Copyright 2022 S.Grottel
>
> Licensed under the Apache License, Version 2.0 (the "License");
> you may not use this file except in compliance with the License.
> You may obtain a copy of the License at
>
> http://www.apache.org/licenses/LICENSE-2.0
>
> Unless required by applicable law or agreed to in writing, software
> distributed under the License is distributed on an "AS IS" BASIS,
> WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
> See the License for the specific language governing permissions and
> limitations under the License.

For details, also see [LICENSE](./LICENSE).
