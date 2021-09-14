
# import trio

# # A regular function
# def regular_double(x):
#     return 2 * x

# # An async function
# async def async_double(x):
#     return 2 * x

# # async def print_double(x):
# #     print(await async_double(x))   # <-- OK!




# async def child1():
#     print("  child1: started! sleeping now...")
#     await trio.sleep(1)
#     print("  child1: exiting!")

# async def child2():
#     print("  child2: started! sleeping now...")
#     await trio.sleep(1)
#     print("  child2: exiting!")

# async def parent():
#     print("parent: started!")
#     async with trio.open_nursery() as nursery:
#         print("parent: spawning child1...")
#         nursery.start_soon(child1)

#         print("parent: spawning child2...")
#         nursery.start_soon(child2)

#         print("parent: waiting for children to finish...")
#         # -- we exit the nursery block here --
#     print("parent: all done!")

# trio.run(parent)



# echo-client.py

# import sys
# import trio
# import serial

# # arbitrary, but:
# # - must be in between 1024 and 65535
# # - can't be in use by some other program on your computer
# # - must match what we set in our echo server
# PORT = 12345
# ser = serial.Serial(
#     port='COM38',
#     baudrate=9600,
#     parity=serial.PARITY_NONE,
#     stopbits=serial.STOPBITS_ONE,
#     bytesize=serial.EIGHTBITS,
#     timeout=1)


# async def sender(ser):
#     print("sender: started!")
#     while True:
#         data = b"async can sometimes be confusing, but I believe in you!\n"
#         print(f"sender: sending {data!r}")
#         await ser.write(data)
#         await trio.sleep(1)

# async def receiver(ser):
#     print("receiver: started!")
#     # async for data in client_stream:
#     #     print(f"receiver: got data {data!r}")
#     # print("receiver: connection closed")
#     data = ser.readline().decode()
#     if data:
#         print(data)
#     sys.exit()

# async def parent():
#     print(f"parent: connecting to 127.0.0.1:{PORT}")
#     global ser
#     async with trio.open_nursery() as nursery:
#         print("parent: spawning sender...")
#         nursery.start_soon(sender, ser)
#         print("parent: spawning receiver...")
#         nursery.start_soon(receiver, ser)

# trio.run(parent)

from trio import run
from trio_serial import SerialStream


async def sender(com, ser):
    print("sender: started!")
    print(com)
    while True:
        data = b"async can sometimes be confusing, but I believe in you!\n"
        print(f"sender: sending {data!r}")
        #await ser.send_all(data)
        await ser.send_all(com + b'\n')
        await trio.sleep(1)

async def receiver(ser):
    print("receiver: started!")
    # async for data in client_stream:
    #     print(f"receiver: got data {data!r}")
    # print("receiver: connection closed")

    buf = await ser.receive_some()
    if buf:
        print(buf)
    #if buf == u'B1-GOOD\r\n':
        await ser.send_all('G0 x100 y100 z100', ser)

async def parent():
    print(f"parent: connecting to port")
    async with SerialStream("COM12") as ser:
        async with trio.open_nursery() as nursery:
            print("parent: spawning receiver...")
            nursery.start_soon(receiver, ser)

            print("parent: spawning sender...")
            nursery.start_soon(sender, ser)

trio.run(parent)