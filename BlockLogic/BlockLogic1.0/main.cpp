#include <iostream>
using namespace std;

/*

//
 SWITCHES
//

Switch transfer
    Positions: 3

    Tracks: 2
        transfer.TrackA StartPos: 0
        transfer.TrackB StartPos: 1

    Linked: false // when tracks > 2, Positions don't need to be adjacent
    // Tracks are considered to be in pos-1 when moving or not locked in place

    ContainsBlocks (start to end of track):
        transfer.TrackA:
            Block transferStorage
        transfer.TrackB:
            Block transferCircuit
    
    When pos0:
    Ahead:
        Block storageB
    Behind:
        NULL

    When pos1:
    Ahead:
        Block storageA
    Behind:
        Block station
    
    When pos2:
    Ahead:
        Block fbr
    Behind:
        SHUTTLE // There is track but no block in this direction


//
 BLOCKS
//

Block station
    Next Block (leave forward):
        0: Block transferCircuit
        1: Block transferStorage

    Next Block (leave backward):
        0: Block multimoveA
        1: Block fbr


    Forward.Exit0:
        // All exits for each block also have the condition that the block its attempting to enter into (the exit's next block) is free
        When Switch transfer.TrackA = pos1

        Dispatch Interval: // The time the block must wait before it can send another train
            30 seconds
        Delay on Arrival:  // 0s: Train must stop. -1s: Train can roll through if allowed to leave
            2 seconds
        Delay on Departure:  // 0s: Train must stop. -1s: Train can roll through if allowed to leave
            0 seconds

    Forward.Exit1:
        When Switch transfer.TrackB = pos1

        Dispatch Interval: // The time the block must wait before it can send another train
            -1 seconds
        Delay on Arrival:  // 0s: Train must stop. -1s: Train can roll through if allowed to leave. If Switch has to move, this is the delay before it moves
            2 seconds
        Delay on Departure:  // 0s: Train must stop. -1s: Train can roll through if allowed to leave
            0 seconds

    Backwards.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            0 seconds
    
    Backwards.Exit1:    // Move right through multimoveB&A without pausing. multimoveB&A must also approve this
        When multimoveB can do its Backwards.Exit0
        When multimoveA can do its Backwards.Exit0

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

Block transferCircuit
    Next Block (leave forward):
        0: Block storageA
        1: Block fbr

    Next Block (leave backward):
        0: Block station
        1: SHUTTLE  // SHUTTLE means that there is track in stated direction, and sending a train will soon return it back to the same block

    Forward.Exit0:
        When Switch transfer.TrackA = pos1

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            2 seconds   // 2s of being parked before Switch transfer will move
        Delay on Departure:
            -1 seconds

    Forward.Exit1:
        When Switch transfer.TrackA = pos2

        Dispatch Interval:
            29 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            3 seconds

    Backwards.Exit0:
        When Switch transfer.TrackA = pos1

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            -1 seconds

    Backwards.Exit1:
        When Switch transfer.TrackA = pos2

        Dispatch Interval:
            29 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            3 seconds

Block transferStorage
    Next Block (leave forward):
        0: Block storageB
        1: Block storageA

    Next Block (leave backward):
        0: NULL // No track in this direction, or previous block cannot be reached
        1: Block station

    Forward.Exit0:
        When Switch transfer.TrackB = pos0

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            0 seconds

    Forward.Exit1:
        When Switch transfer.TrackB = pos1

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            -1 seconds

    Backwards.Exit1:
        When Switch transfer.TrackB = pos1

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            2 seconds
        Delay on Departure:
            -1 seconds

Block fbr
    Next Block (leave forward):
        0: Block multimoveA
        1: Block station
    
    Forward.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

    Forward.Exit1:    // Move right through multimoveA&B without pausing. multimoveA&B must also approve this
        When multimoveA can do its Forward.Exit0
        When multimoveB can do its Forward.Exit0

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

Block multimoveA
    Next Block (leave forward):
        0: Block multimoveB
    Next Block (leave backward):
        0: Block fbr
    
    Forward.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

    Backwards.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds


Block multimoveB
    Next Block (leave forward):
        0: Block station
    Next Block (leave backward):
        0: Block multimoveA
    
    Forward.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

    Backwards.Exit0:
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            -1 seconds
        Delay on Departure:
            -1 seconds

Block storageA
    Next Block (leave forward):

    Next Block (leave backward):
        0: Block transferCircuit
        1: Block transferStorage

    Backwards.Exit0:
        When Switch transfer.TrackA = pos1
        
        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            0 seconds
        Delay on Departure:
            0 seconds

    Backwards.Exit1:
        When Switch transfer.TrackB = pos1

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            0 seconds
        Delay on Departure:
            0 seconds

Block storageB
    Next Block (leave forward):

    Next Block (leave backward):
        0: Block transferStorage

    Backwards.Exit0:
        When Switch transfer.TrackB = pos0

        Dispatch Interval:
            -1 seconds
        Delay on Arrival:
            0 seconds
        Delay on Departure:
            0 seconds

//
 TIRES
//

// All tires should only activate when the train is physically on their "Controlled by" block,

Tire station1
    Controlled by:
        Block station
    Falls within zones of:
        Ahead: // In order of closest to farthest
            Block transferCircuit
                *WHEN Switch transfer.TrackA = pos1
            Block transferStorage
                *WHEN Switch transfer.TrackB = pos1
        Behind: // In order of closest to farthest
            Block fbr

Tire station2
    Synced with:
        Tire station1

Tire transferCircuit1
    Controlled by:
        Block transferCircuit
    Falls within zones of:
        Ahead:
            Block storageA
            Block fbr
        Behind:
            Block station

Tire multimoveA1 // the multimoveA block is the first tire in the station zone
    Controlled by:
        Block multimoveA
    Falls within zones of:
        Ahead:
            Block multimoveB
            Block station
            Block transferCircuit
                *WHEN Switch transfer.TrackA = pos1
            Block transferStorage
                *WHEN Switch transfer.TrackB = pos1
        Behind:
            Block fbr

Tire multimoveB1 // the multimoveB block is the second tire in the station zone
    Controlled by:
        Block multimoveB
    Falls within zones of:
        Ahead:
            Block station
            Block transferCircuit
                *WHEN Switch transfer.TrackA = pos1
            Block transferStorage
                *WHEN Switch transfer.TrackB = pos1
        Behind:
            Block multimoveA
            Block fbr

Tire fbr1
    Controlled by:
        Block fbr
    Falls within zones of:
        Ahead:
            Block multimoveA
            Block multimoveB
            Block station

Tire fbr2
    Synced with:
        Tire fbr1

Tire fbr3
    Synced with:
        Tire fbr1

Tire transferCircuit1
    Controlled by:
        Block transferCircuit
    Falls within zones of:
        Ahead:
            Block storageA
                *WHEN Switch transfer.TrackA = pos1
        Behind:
            Block station
                *WHEN Switch transfer.TrackA = pos1
        Retract & Disabled while:  // Defaults to raised
            Block transferCircuit: request to launch
            Only retract and disable if: // All conditions must be met
                Block transferCircuit.train = PARKED
                Switch transfer.TrackA = pos2 // Still locked
            Only raise if: // All conditions must be met
                Block transferCircuit = free
                    OR Block transferCircuit.train = PARKED
                    OR Launch main.train.velocity = 0 // Any segment in launch main
                Switch transfer.TrackA = pos2 // Still locked
                    OR Switch transfer.TrackA = any other pos

Tire transferCircuit2
    Synced with:
        Tire transferCircuit1

Tire transferCircuit3
    Synced with:
        Tire transferCircuit1

Tire transferStorage1
    Controlled by:
        Block transferStorage
    Falls within zones of:
        Ahead:
            Block storageB
                *WHEN Switch transfer.TrackB = pos0
            Block storageA
                *WHEN Switch transfer.TrackB = pos1
        Behind:
            Block station
                *WHEN Switch transfer.TrackB = pos1

Tire transferStorage2
    Synced with:
        Tire transferStorage1

Tire transferStorage3
    Synced with:
        Tire transferStorage1

Tire storageA1
    Controlled by:
        Block storageA
    Falls within zones of:
        Behind:
            Block transferCircuit
                *WHEN Switch transfer.TrackA = pos1
            Block transferStorage
                *WHEN Switch transfer.TrackB = pos1

Tire storageB1
    Controlled by:
        Block storageB
    Falls within zones of:
        Behind:
            Block transferStorage
                *WHEN Switch transfer.TrackB = pos0


//
 LAUNCHES
//
Launch main
    Type: Magnetic
    Direction: Bidirectional
    RollingLaunch: true

Launch main Segment transfer
    Part of Block transferCircuit
        *WHEN Switch transfer.TrackA = pos2
    DISABLED if Switch transfer.TrackA = any other pos

Launch main Segment spike
    Part of Block transferCircuit
        *WHEN Switch transfer.TrackA = pos2
    DISABLED if Switch transfer.TrackA = any other pos

Launch main Segment tophat
    Part of Block transferCircuit
        *WHEN Switch transfer.TrackA = pos2
    DISABLED if Switch transfer.TrackA = any other pos

*/

class Block {
    public:
        Block() {
            cout << "Block created" << endl;
        }
};

/*class Switch : public Block {
    public:
        Switch() {
            cout << "Switch created" << endl;
        }
};

class Station : public Block {
    public:
        Station() {
            cout << "Station created" << endl;
        }
};*/

int main() {

}

