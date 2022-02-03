// Fill out your copyright notice in the Description page of Project Settings.


#include "CellEditorWidget.h"
//#include "../MyD/Cells/HexCell.h"
#include "EditorLevelLibrary.h"

void UCellEditorWidget::CreateCells(int gridWidth, int gridHeight)
{
	TArray<TArray<AHexCell*>> gridArray;
	gridArray.SetNumZeroed(gridWidth);
	for (int x = 0; x < gridWidth; x++)
	{
		gridArray[x].SetNumZeroed(gridHeight);

		for (int y = 0; y < gridHeight; y++)
		{
			int oddRow = y % 2;
			const float xPos = x * XOffset + OddOffset * oddRow;
			const float yPos = y * YOffset;

			AHexCell* newCell = GetWorld()->SpawnActor<AHexCell>(BaseCell, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);

			int q = x - (y - y % 2) / 2;
			newCell->hexCoord = FIntPoint(q, y);
			gridArray[x][y] = newCell;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//APawn* pawn = GetWorld()->SpawnActor<APawn>(testPawn, gridArray[0][0]->GetActorLocation(), FRotator::ZeroRotator);
	//controller = Cast<AMyController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//////////////////////////////////////////////////////////////////////////////

	// Set neighbours
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			bool oddRow = y % 2 == 1;
			if (y > 0)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x][y - 1]);

				if (oddRow)
				{
					if (x < gridWidth - 1)
						gridArray[x][y]->neighbours.Add(gridArray[x + 1][y - 1]);
				}
				else
				{
					if (x > 0)
						gridArray[x][y]->neighbours.Add(gridArray[x - 1][y - 1]);
				}
			}

			if (y < gridHeight - 1)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x][y + 1]);

				if (oddRow)
				{
					if (x < gridWidth - 1)
						gridArray[x][y]->neighbours.Add(gridArray[x + 1][y + 1]);
				}
				else
				{
					if (x > 0)
						gridArray[x][y]->neighbours.Add(gridArray[x - 1][y + 1]);
				}
			}

			if (x > 0)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x - 1][y]);
			}

			if (x < gridWidth - 1)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x + 1][y]);
			}
		}
	}
}

void UCellEditorWidget::CreateSpawnPoint(bool team)
{
	TArray<AActor*> selection = UEditorLevelLibrary::GetSelectedLevelActors();

	for (AActor* selected : selection)
	{
		AHexCell* cell = Cast<AHexCell>(selected);

		if (cell)
		{
			ASpawnPoint* newPoint = GetWorld()->SpawnActor<ASpawnPoint>(spawnPoint, cell->GetActorLocation(), FRotator::ZeroRotator);
			newPoint->SetPoint(team, cell);
		}
	}
}

void UCellEditorWidget::RemoveCell()
{
	TArray<AActor*> selection = UEditorLevelLibrary::GetSelectedLevelActors();

	for (AActor* selected : selection)
	{
		AHexCell* cell = Cast<AHexCell>(selected);

		if (cell)
		{
			for (auto neighbour : cell->neighbours)
			{
				neighbour->neighbours.Remove(cell);
			}
			UEditorLevelLibrary::DestroyActor(selected);
		}
	}
}

void UCellEditorWidget::Reset()
{
	TArray<AActor*> allCells = UEditorLevelLibrary::GetAllLevelActors();
	for (auto actor : allCells)
	{
		if (Cast<AHexCell>(actor) || Cast<ASpawnPoint>(actor))
		{
			UEditorLevelLibrary::DestroyActor(actor);
		}
	}

}

void UCellEditorWidget::ChangeCellType(ECellType type)
{
	TArray<AActor*> selection = UEditorLevelLibrary::GetSelectedLevelActors();

	for(AActor* selected: selection)
	{
		AHexCell* cell = Cast<AHexCell>(selected);

		if (cell)
		{
			cell->cellType = type;


#define CASE_TYPE_WEIGHT_MAT(_TYPE, _WEIGHT, _MAT)\
			case _TYPE:\
			cell->weight = _WEIGHT;\
			cell->defaultMat = _MAT;\
			cell->cellMesh->SetMaterial(0, _MAT);\
			break

			switch (type)
			{
				CASE_TYPE_WEIGHT_MAT(ECellType::Base, 1, defaultMat);
				CASE_TYPE_WEIGHT_MAT(ECellType::Sand, 2, sandMat);
				CASE_TYPE_WEIGHT_MAT(ECellType::Water, 3, waterMat);
				CASE_TYPE_WEIGHT_MAT(ECellType::Obstacle, 99, obstacleMat);
			}

#undef CASE_TYPE_WEIGHT_MAT

		}
	}
}
