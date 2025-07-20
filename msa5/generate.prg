* Generate nine 5-stage bit swizzle patterns

IF .t.
	* Make some of the characters capitalized, which indicates they will be processed differently than the other ones
	DIMENSION laOps[9]
	laOps[1] = '"d40u75shpl3cmon2tjbr9fvq8ak61gie", "7h03p8atsmqce2f9kv4li1d5ugbojnr6", "k6uhmf0vdetagpslr2ob94j3i158qnc7", "ch4t725or163nbje9sqlkmvf0iapdug8", "tp9ishcn8vk0fumbe2ql415jg3rdoa76"'
	laOps[2] = '"oukr15ie632478lmcv0nbp9shfaqtgjd", "t0pufs1d2r3ghvmk4el5oqj789n6abic", "r8iufchqo56p1asmeg37j20kvbdtn9l4", "tfidp0e9lk3aron68gjc7qb5v124usmh", "8peuqndhf2c9lgst6o7br1m4jvk53a0i"'
	laOps[3] = '"n1u856ob3ijsekd02f7ma4vtgp9hqcrl", "iaodknj165mursq0t9gpvb438ec2f7lh", "nvikq5tr3g842p1mlfcajb0o9h6u7des", "d3jfqv08o71is2l4nbk9uacgrep5mh6t", "8loc4tkv9p0ug6ab17dsrnih32jem5qf"'
	laOps[4] = '"osclaq6je9bd7r31gv8k0hfit4npum52", "lqdfju5i9pgm7b4etharo68k20vsc13n", "da7r5q2n89glj1mbsefip4th06u3vokc", "mec0vas7jdbf93guirnk5qp8ho14t6l2", "5ndvlcf8qg39hobum02tes7j14ika6rp"'
	laOps[5] = '"v5arl1qdgmie9chjt2uobs83k76pf0n4", "2lovucfsgt9806rmidq47kbj35eh1pna", "ugb192pld8cm3frs0netqok64ih5va7j", "ovchlnq7kb9ij86apt2e03g4u1rm5fds", "i29308t4n1cdslh7qapkjbuvmg5efr6o"'
	laOps[6] = '"1gb2umai3cqpkn740do9l8jvst5rf6he", "cis9ru7f8md20pj5hngakleo6b4v31tq", "udgke3t827om5pfcv9lh1iqsarn6bj40", "2ubdfqjgipn19cao0vt347ls8mekr6h5", "61t7sil8hu2fqc50a9rp3d4gbenvojkm"'
	laOps[7] = '"t3pjvmg80an1f7bqc6s52hulierod49k", "sqgk7jc9lbf8mhe203oi1un5pvrta46d", "pjkbdl17o2v6m09cathfrsu5g83eqn4i", "loe1kn2fmjc75943sqtg8iaup6dv0brh", "qelof32jrg0ai9tdmc7p81kuhbn5v4s6"'
	laOps[8] = '"sdkhba6ue8cfm3tvrg5q27n4jpol91i0", "f143c9lh60s7nokamegbqi2uptrjv85d", "clsvafigod3t95u08e6nkh7p41rbm2jq", "ihfsol42k7u8g0r1nad5v6jt39pqebmc", "dfesa6o9qu120l7g54t8ip3bmrvncjhk"'
	laOps[9] = '"9813ivosjtmcanh02reld6u7bq5gk4fp", "7gdr9a2tmvl6j0fqpo5b4i3u1schen8k", "0e78hmn6aq3pulr5ks1gcf4bi9jvd2ot", "7lgfu2djpnr9145iscoqbt3ha06mve8k", "iue50qd17ch26omlsgrv43tfjb9pk8na"'

	lcOut = SPACE(0)
	FOR lnI = 1 TO ALEN(laOps, 1)
		lcOp = laOps[lnI]
		FOR lnJ = 1 TO LEN(lcOp)
			IF found_in(TRANSFORM(lnJ), TRANSFORM(RAND()))
				lcOp = STUFF(lcOp, lnJ, 1, UPPER(SUBSTR(lcOp, lnJ, 1)))
			ENDIF
		NEXT
		laOps[lnI]	= lcOp
		lcOut		= lcOut + lcOp + CHR(13)
	NEXT
	
	_cliptext = lcOut
	CANCEL
ENDIF


lcOut = SPACE(0)
FOR lnPass = 1 TO 5 STEP 1
	FOR lnOp = 1 TO 9 STEP 0
		lcString = SPACE(0)
		FOR lnI = 1 TO 32 STEP 0
			lcC = get_symbol(INT(RAND() * 32))
			IF NOT lcC $ lcString
				lcString = lcString + lcC
				lnI = lnI + 1
			ENDIF
		NEXT
		IF lcString $ lcOut
			* No duplicates
			LOOP
		ENDIF
		lnOp = lnOp + 1
		lcOut = lcOut + lcString + CHR(13)
	NEXT
	lcOut = lcOut + CHR(13)
NEXT

* Validate it
ALINES(laLines, lcOut)
FOR lnI = 1 TO ALEN(laLines, 1)
	lcLine = laLines[lnI]
	IF EMPTY(lcLine)
		LOOP
	ENDIF
	
	FOR lnJ = 0 TO 31
		lcC = get_symbol(lnJ)
		IF NOT lcC $ lcLine
			SET STEP ON
		ENDIF
	NEXT
NEXT

_cliptext = lcOut




FUNCTION get_symbol
LPARAMETERS tnNum

	IF tnNum <= 9
		RETURN CHR(ASC("0") + tnNum)
	ENDIF
	
	RETURN CHR(ASC("a") + tnNum - 10)

ENDFUNC




FUNCTION found_in
LPARAMETERS tcHaystack, tcNeedle
LOCAL lnI

	FOR lnI = 1 TO LEN(tcNeedle)
		IF SUBSTR(tcNeedle, lnI, 1) $ tcHaystack
			RETURN .t.
		ENDIF
	NEXT
	
	RETURN .f.

ENDFUNC
