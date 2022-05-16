SHIFT←{0,⍵}
DOCK←{(⍵×⍳⍴⍵),0}
STEP←{(SHIFT ⍵)+(DOCK ⍵)}
BELL←{+/ (STEP⍣(⍵-1)) 1⍴1}
{⎕←BELL ⍵}¨⍳10