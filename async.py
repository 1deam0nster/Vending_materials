# import time
# import asyncio



# start = time.time()


# def tic():
#     return 'at %1.1f seconds' % (time.time() - start)


# async def gr1():
#     # Busy waits for a second, but we don't want to stick around...
#     print('gr1 started work: {}'.format(tic()))
#     await asyncio.sleep(2)
#     print('gr1 ended work: {}'.format(tic()))


# async def gr2():
#     # Busy waits for a second, but we don't want to stick around...
#     print('gr2 started work: {}'.format(tic()))
#     await asyncio.sleep(2)
#     print('gr2 Ended work: {}'.format(tic()))


# async def gr3():
#     print("Let's do some stuff while the coroutines are blocked, {}".format(tic()))
#     await asyncio.sleep(1)
#     print("Done!")


# ioloop = asyncio.get_event_loop()
# tasks = [
#     ioloop.create_task(gr1()),
#     ioloop.create_task(gr2()),
#     ioloop.create_task(gr3())
# ]
# ioloop.run_until_complete(asyncio.wait(tasks))
# ioloop.close()
import serial
import time
import asyncio


async def main():
a1 = serial.Serial('COM12', 9600)

    a1.write(b'G0 x20\n')
    await asyncio.sleep(1.0)
    print(f'{time.ctime()} block have data!')
    loop.stop()


def blocking():
    data = a1.read()
    print(data)


loop = asyncio.get_event_loop()

loop.create_task(main())
loop.run_in_executor(None, blocking)

loop.run_forever()

pending = asyncio.Task.all_tasks(loop=loop)
group = asyncio.gather(*pending)
loop.run_until_complete(group)
loop.close()
