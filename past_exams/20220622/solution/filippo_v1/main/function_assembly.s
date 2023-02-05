				AREA asm_func, CODE, READONLY
				EXPORT monotono_crescente

monotono_crescente	push {r4-r8, lr}

check_monotonic		mov r3, #0 ; Initialize the loop counter to zero
					ldrb r2, [r0, r3] ; Load the first value from the array
					add r3, r3, #1 ; Increment the loop counter
					cmp r3, r1 ; Compare the loop counter with the size of the array
					bge done ; If it's equal or greater, branch to done

loop				ldrb r5, [r0, r3] ; Load the next value from the array
					cmp r5, r2 ; Compare it with the previous value
					bgt next ; If it's greater, branch to next
					mov r0, #0x55 ; Return 0x55 to indicate that the vector is not monotonic
					pop {r4-r8, pc} ; Restore r4 and pc from the stack

next				mov r2, r5 ; Save the current value as the previous value
					add r3, r3, #1 ; Increment the loop counter
					cmp r3, r1 ; Compare the loop counter with the size of the array
					blt loop ; If it's smaller, repeat the loop

done				mov r0, #0xFF ; Return 0xFF to indicate that the vector is monotonic
					pop {r4-r8, pc} ; Restore r4 and pc from the stack
					
				END
