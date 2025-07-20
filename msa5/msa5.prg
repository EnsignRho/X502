DECLARE INTEGER msa5_compute ;
	IN "C:\temp\msvc++\msa51\msa5\msa5.dll" ;
	STRING		cData, ;
	INTEGER		nDataLength, ;
	INTEGER		nAlgorithm, ;
	INTEGER		@x, ;
	INTEGER		@y, ;
	INTEGER		@t, ;
	INTEGER		@u, ;
	INTEGER		@v, ;
	STRING		@x8, ;
	STRING		@y8, ;
	STRING		@t8, ;
	STRING		@u8, ;
	STRING		@v8, ;
	INTEGER		lContinuation

DECLARE INTEGER msa5_sha1 ;
	IN "C:\temp\msvc++\msa51\msa5\msa5.dll" ;
	STRING		cData, ;
	INTEGER		nDataLength, ;
	INTEGER		@x, ;
	INTEGER		@y, ;
	INTEGER		@t, ;
	INTEGER		@u, ;
	INTEGER		@v, ;
	STRING		@x8, ;
	STRING		@y8, ;
	STRING		@t8, ;
	STRING		@u8, ;
	STRING		@v8

PUBLIC glDoLines, gnMaxFileSize
glDoLines		= .f.
gnMaxFileSize	= 100000

SET BLOCKSIZE TO 32

CREATE CURSOR c_results ;
( ;
	cFile		c(240), ;
	nLineNo		i, ;
	cLine		c(120), ;
	algo		i, ;
	cMsa5		c(40), ;
	cSha1		c(40) ;
)

SELECT * ;
	FROM c_results ;
	INTO CURSOR c_results_dups READWRITE

lcPath = "c:\libsf\"

recurse_folders(lcPath)

process_dups()

SELECT c_results_dups
BROWSE LAST NOWAIT




FUNCTION recurse_folders
LPARAMETERS lcPath
LOCAL ARRAY laExts[1]
LOCAL ARRAY laFiles[1]
LOCAL ARRAY laLines[1]
LOCAL lnI, lnJ, lnA, lcFile, lcLine, lnRet, xi, yi, ti, ui, vi, x8, y8, t8, u8, v8

	DIMENSION laExts[1]
	laExts[1] = "*.*"
	
	IF NOT ".git" $ LOWER(lcPath)
		*IF RECCOUNT("c_results") > 5000
		*	process_dups()
		*ENDIF
		FOR lnPass = 1 TO ALEN(laExts, 1)
			ADIR(laFiles, lcPath + laExts[lnPass])
			IF TYPE("laFiles[1,1]") = "C"
				FOR lnI = 1 TO ALEN(laFiles, 1)
					lcFile = laFiles[lnI, 1]
					IF LOWER(JUSTEXT(lcFile)) + "|" $ "exe|dll|pdb|ipch|obj|lib|"
						LOOP
					ENDIF
					
					WAIT WINDOW lcPath + lcFile NOWAIT
					IF glDoLines OR LOWER(JUSTEXT(lcFile)) + "|" $ "prg|cpp|h|txt|asm|inc|asp|bat|"
						* Do line-by-line
						DIMENSION laLines[1]
						laLines = .f.
						ALINES(laLines, FILETOSTR(lcPath + lcFile))
						IF TYPE("laLines[1]") = "C"
							FOR lnJ = 1 TO ALEN(laLines, 1)
								lcLine = laLines[lnJ]
								IF NOT EMPTY(lcLine)
									FOR lnA = 0 TO 8
										* MSHA5x for this block
										STORE 0 TO xi, yi, ti, ui, vi
										STORE SPACE(16) TO x8, y8, t8, u8, v8
										lnRet = msa5_compute(lcLine, LEN(lcLine), lnA, @m.xi, @m.yi, @m.ti, @m.ui, @m.vi, @m.x8, @m.y8, @m.t8, @m.u8, @m.v8, 0)
										
										INSERT INTO c_results (cFile, nLineNo, cLine, algo, cMsa5) ;
												VALUES (lcPath + lcFile, ;	&& cFile
														lnJ, ;				&& nLineNo
														lcLine, ;			&& cLine
														lnA, ;				&& algo
														LEFT(m.x8,8) + LEFT(m.y8,8) + LEFT(m.t8,8) + LEFT(m.u8,8) + LEFT(m.v8,8))	&& cMsa5
										
										* SHA-1 for this block
										IF lnA = 0
											STORE 0 TO xi, yi, ti, ui, vi
											STORE SPACE(16) TO x8, y8, t8, u8, v8
											lnRet  = msa5_sha1(lcLine, LEN(lcLine), @m.xi, @m.yi, @m.ti, @m.ui, @m.vi, @m.x8, @m.y8, @m.t8, @m.u8, @m.v8)
											lcSha1 = LEFT(m.x8,8) + LEFT(m.y8,8) + LEFT(m.t8,8) + LEFT(m.u8,8) + LEFT(m.v8,8)
										ENDIF
										REPLACE cSha1 WITH lcSha1 ;
											IN c_results
									NEXT
								ENDIF
							NEXT
						ENDIF
					ENDIF
					IF NOT glDoLines
						* Do the whole file
						TRY
							lcData = FILETOSTR(lcPath + lcFile)
						CATCH
							lcData = SPACE(0)
						ENDTRY
						IF NOT EMPTY(lcData) AND LEN(lcData) < gnMaxFileSize
							FOR lnA = 0 TO 8
								* MSHA5x for this block
								STORE 0 TO xi, yi, ti, ui, vi
								STORE SPACE(16) TO x8, y8, t8, u8, v8
								lnRet = msa5_compute(lcData, LEN(lcData), lnA, @m.xi, @m.yi, @m.ti, @m.ui, @m.vi, @m.x8, @m.y8, @m.t8, @m.u8, @m.v8, 0)
								
								INSERT INTO c_results (cFile, nLineNo, algo, cMsa5) ;
										VALUES (lcPath + lcFile, ;		&& cFile
												1, ;					&& nLineNo
												lnA, ;					&& algo
												LEFT(m.x8,8) + LEFT(m.y8,8) + LEFT(m.t8,8) + LEFT(m.u8,8) + LEFT(m.v8,8))	&& cMsa5
										
								* SHA-1 for this block
								IF lnA = 0
									STORE 0 TO xi, yi, ti, ui, vi
									STORE SPACE(16) TO x8, y8, t8, u8, v8
									lnRet = msa5_sha1(lcData, LEN(lcData), @m.xi, @m.yi, @m.ti, @m.ui, @m.vi, @m.x8, @m.y8, @m.t8, @m.u8, @m.v8)
									lcSha1 = LEFT(m.x8,8) + LEFT(m.y8,8) + LEFT(m.t8,8) + LEFT(m.u8,8) + LEFT(m.v8,8)
								ENDIF
								REPLACE cSha1 WITH lcSha1 ;
									IN c_results
							NEXT
						ENDIF
					ENDIF
				NEXT
			ENDIF
		NEXT

		DIMENSION laFiles[1]
		laFiles = .f.
		ADIR(laFiles, lcPath + "*.", "D")
		
		IF TYPE("laFiles[1,1]") = "C"
			FOR lnI = 1 TO ALEN(laFiles, 1)
				IF NOT laFiles[lnI, 1] == "." AND NOT laFiles[lnI, 1] == ".."
					recurse_folders(ADDBS(lcPath + LOWER(laFiles[lnI, 1])))
				ENDIF
			NEXT
		ENDIF
	ENDIF
	
ENDFUNC




FUNCTION process_dups

	IF glDoLines
		SELECT cFile, cLine, algo, cMsa5, SUM(00001) as nCount ;
			FROM c_results ;
			GROUP BY cFile, cLine, algo, cMsa5 ;
			ORDER BY cFile, cLine, algo, cMsa5 ;
			INTO CURSOR c_totals ;
			HAVING nCount > 1

		SELECT * ;
			FROM c_results ;
			WHERE PADR(ALLTRIM(cFile) + ALLTRIM(cLine) + TRANSFORM(algo) + ALLTRIM(cMsa5), 240) IN (SELECT PADR(ALLTRIM(cFile) + ALLTRIM(cLine) + TRANSFORM(algo) + ALLTRIM(cMsa5), 240) FROM c_totals) ;
			ORDER BY algo, cLine, cMsa5, cSha1, cFile, nLineNo ;
			INTO CURSOR c_dup_results READWRITE

		BROWSE LAST NOWAIT

		SELECT c_dup_results
		lcLastCode = "zebra"
		lcLastMsa5 = "zebra"
		lnLastAlgo = -1
		SCAN
			IF NOT lcLastMsa5 == cMsa5 OR lnLastAlgo != algo
				lnLastAlgo = algo
				lcLastMsa5 = cMsa5
				lcLastCode = cLine
			ELSE
				IF NOT lcLastCode == cLine
					DELETE
				ENDIF
			ENDIF
		ENDSCAN
		
	ELSE
		SELECT cMsa5 AS cSig, SUM(0001) AS nCount ;
			FROM c_results ;
			GROUP BY 1 ;
			INTO CURSOR c_dups ;
			HAVING nCount > 1
		
		SET ENGINEBEHAVIOR 70
		SELECT * ;
			FROM c_results ;
			WHERE cMsa5 IN (SELECT cSig FROM c_dups) ;
			ORDER BY cMsa5, cSha1, cFile, nLineNo ;
			INTO CURSOR c_dup_results
		SET ENGINEBEHAVIOR 70
		
		lcAddList = SPACE(0)
		SELECT c_dup_results
		lcMsa5 = "zebra"
		lcFile = SPACE(0)
		SCAN
			IF NOT cMsa5 == lcMsa5
				lcMsa5 = cMsa5
				lcFile = ALLTRIM(cFile)
				lcData = FILETOSTR(lcFile)
				LOOP
			ENDIF
			
			IF NOT lcData == FILETOSTR(ALLTRIM(cFile))
				lcAddList = lcAddList + cMsa5 + CHR(13)
			ENDIF
		ENDSCAN
		
		IF NOT EMPTY(lcAddList)
			INSERT INTO c_results_dups ;
				SELECT * FROM c_dup_results ;
					WHERE cMsa5 $ lcAddList
			
			SELECT c_results_dups
			GOTO BOTTOM
			SKIP -50
			BROWSE LAST NOWAIT
		ENDIF
	ENDIF
	
	SELECT c_results
	SET SAFETY OFF
	ZAP
	SET SAFETY ON

ENDFUNC
