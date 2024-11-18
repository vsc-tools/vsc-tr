
# Assumptions
- Type, Descriptor, String, Metadata block can be read into memory


# Block Types
- Header block
- Stream Descriptor block
- Metadata block
- Type block
- String block

# Terminator Block
Last block in the file. Has pointers to the end of the relevant
chains of data blocks
- type-block pointer
- stream-descriptor pointer
- List of stream-data pointers (1 for each active stream at this point in the file)
- string-table pointer


# Block structure
- size (unsigned) - size of the payload, excluding the bytes of 'size'
- type 
- flags (eg compressed)
- prev-block pointer (abs, unsigned)
- type-data 

Note: means that we have to write blocks in pairs

## Flags
- Compressed

# Header Block
Note: The header block is written with uncompressed values
- magic 'v' 't' 'r' 0
- version
- timescale 
- timeunit

# Stream-Descriptor Block
- Array of
  - name
  - Stream-Data Pointer
  - type set 

# String Table Block
- Array of strings

# Stream-Data Block
- <base>
- last end time (abs, unsigned)
- earliest start time (offset of last end, signed)
- transactions

# Transaction
- sz
- start time
- end time
- type-id
- data

# DataType Desc Block
- <base>
- list-of desc

# DataType Desc
- sz
- type
- data

## Integer Type
- sz
- type
- is_signed
- width

## Enum TYpe
- sz
- type
- base type-id (?)
- num_enumerators
  - name-id
  - value

## Struct Type
- sz
- type
- num_fields
- fields
  - name-id
  - type-id

## Array Type
- sz
- type
- element type-id
- array-sz

## List Type
- sz
- type
- element type-id

Key is to max-size. 
- Have size of block data that was incrementally packed
- Know max size of header data (eg times)
- Know max size of base data

Overhead is:
- max 20 bytes + max 24 bytes -> max 48 bytes
  - 2% on a 4k block size
  - 1% on a 8k block size
  - 0.5% on a 16k block size

Target an approximate size, but keeping Nk blocks is not a requirement
Dump a block once its data exceeds the target size
Could try to be adaptive based on average transaction size, average compression ratio

Leading-zero suppression
1, 2, 4, 8 bytes - 
- 2 bits to capture total size
- 

- Leading-zero suppression
- Zig-zag encoding
- Split encoding

Leading byte should indicate scheme+

7 bits per byte
0..0x3F
0..0x0000_3FFF
0..0x001F_FFFF
0..0x0FFF_FFFF
0..0x0FFF_FFFF

Leading-zero

