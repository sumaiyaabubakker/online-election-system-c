#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_VOTERS 5
#define MAX_CANDIDATES 3

char voterIDs[MAX_VOTERS][20] = 
{
    "25K-0001",
    "25K-0002",
    "25K-0003",
    "25K-0004",
    "25K-0005"
	
};

char passwords[MAX_VOTERS][20] = {"p1", "p2", "p3", "p4", "p5"};
char candidates[MAX_CANDIDATES][20] = {"Imran", "Nawaz", "Altaf"};

int hasVoted[MAX_VOTERS] = {0};
int votes[MAX_CANDIDATES] = {0};
int totalVotes = 0;
int totalInvalidAttempts = 0;

// PROGRESS SAVE SYSTEM

void saveProgress()
{
    FILE *fp = fopen("progress.txt", "w");
    if (!fp)
        return;

    for (int i = 0; i < MAX_VOTERS; i++)
        {
        	fprintf(fp, "%d ", hasVoted[i]);
		}
    fprintf(fp, "\n");

    for (int i = 0; i < MAX_CANDIDATES; i++)
        {
        	fprintf(fp, "%d ", votes[i]);
		}
    fprintf(fp, "\n");

    fprintf(fp, "%d\n", totalVotes);
    fprintf(fp, "%d\n", totalInvalidAttempts);

    fclose(fp);
}

void loadProgress()
{
    FILE *fp = fopen("progress.txt", "r");
    if (!fp)
        return;

    for (int i = 0; i < MAX_VOTERS; i++)
        {
        	fscanf(fp, "%d", &hasVoted[i]);
		}

    for (int i = 0; i < MAX_CANDIDATES; i++)
        {
        	fscanf(fp, "%d", &votes[i]);
		}

    fscanf(fp, "%d", &totalVotes);
    fscanf(fp, "%d", &totalInvalidAttempts);

    fclose(fp);
}

// VOTER STATUS FILE

void updateVoterStatusFile()
{
    FILE *fp = fopen("voter_status.txt", "w");
    if (!fp)
        return;

    fprintf(fp, "Voter Status:\n---------------------\n");

    for (int i = 0; i < MAX_VOTERS; i++)
    {
        if (hasVoted[i] == 1)
            {
            	fprintf(fp, "%s - VOTED\n", voterIDs[i]);
			}
        else
            {
            	fprintf(fp, "%s - NOT VOTED\n", voterIDs[i]);
			}
    }

    fclose(fp);
}

// LOGGING INTO TXT FILES

void writeLog(char message[])
{
    FILE *fp = fopen("log.txt", "a");
    if (!fp)
        return;

    time_t now = time(NULL);
    fprintf(fp, "%s - %s", message, ctime(&now));
    fclose(fp);
}

// FUNCTIONS FOR THE SYSTEM

int login(char id[], char pass[])
{
    for (int i = 0; i < MAX_VOTERS; i++)
    {
        if (strcmp(id, voterIDs[i]) == 0 && strcmp(pass, passwords[i]) == 0)
        {
            writeLog("Successful login");
            return i;
        }
    }
    writeLog("Failed login");
    return -1;
}

void displayCandidates()
{
    printf("\nCandidates\n");
    for (int i = 0; i < MAX_CANDIDATES; i++)
        {
        	printf("%d. %s\n", i + 1, candidates[i]);
		}
}

void saveResultsToFile()
{
    FILE *fp = fopen("results.txt", "w");
    if (!fp)
        return;

    fprintf(fp, "Current Election Results\n------------------------\n");

    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        float percent = (totalVotes == 0) ? 0 : (votes[i] * 100.0 / totalVotes);
        fprintf(fp, "%s : %d votes (%.2f%%)\n", candidates[i], votes[i], percent);
    }

    fprintf(fp, "\nTotal invalid attempts: %d\n", totalInvalidAttempts);
    fclose(fp);
}

void castVote(int voterIndex)
{
    int choice;

    displayCandidates();
    printf("\nEnter your choice (1-%d): ", MAX_CANDIDATES);
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_CANDIDATES)
    {
        printf("\nInvalid candidate choice!\n");
        totalInvalidAttempts++;
        writeLog("Invalid vote attempt");
        saveProgress();
        return;
    }

    votes[choice - 1]++;
    hasVoted[voterIndex] = 1;
    totalVotes++;

    writeLog("Vote cast successfully");

    updateVoterStatusFile();
    saveResultsToFile();
    saveProgress();

    time_t now = time(NULL);
    printf("\nVote Recorded Successfully!\nTimestamp: %s\n", ctime(&now));
}

void showLeaderboard()
{
    FILE *fp = fopen("leaderboard.txt", "w");
    if (!fp)
        return;

    printf("\n       FINAL LEADERBOARD      \n");
    fprintf(fp, "FINAL LEADERBOARD\n---------------------------\n");
    
 
    if (totalVotes == 0)
    {
        printf("\nNo votes have been cast yet.\n");
        fprintf(fp, "\nNo votes have been cast yet.\n");
        fclose(fp);
        return;
    }

    int highestVotes = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++)
        {
        	if (votes[i] > highestVotes)
            {
            	highestVotes = votes[i];
			}
		}

    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        float percent = (votes[i] * 100.0 / totalVotes);
        printf("%s : %d votes (%.2f%%)\n", candidates[i], votes[i], percent);
        fprintf(fp, "%s : %d votes (%.2f%%)\n", candidates[i], votes[i], percent);
    }

    int tieCount = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++)
        {
        	if (votes[i] == highestVotes)
            {
            	tieCount++;
			}
		}

    if (tieCount > 1)
    {
        printf("\nIt's a TIE between:\n");
        fprintf(fp, "\nTIE between:\n");
        for (int i = 0; i < MAX_CANDIDATES; i++)
            if (votes[i] == highestVotes)
            {
                printf("- %s\n", candidates[i]);
                fprintf(fp, "- %s\n", candidates[i]);
            }
    }
    else
    {
        for (int i = 0; i < MAX_CANDIDATES; i++)
            if (votes[i] == highestVotes)
            {
                printf("\nWINNER: %s\n", candidates[i]);
                fprintf(fp, "\nWINNER: %s\n", candidates[i]);
                break;
            }
    }

    fclose(fp);
}

// MAIN

int main()
{
    char id[20], pass[20];
    int voterIndex;

    loadProgress();
    updateVoterStatusFile();

    while (totalVotes < MAX_VOTERS)
    {

        printf("\nONLINE ELECTION SYSTEM\nEnter Voter ID (or type 'exit' to quit): ");
        scanf("%s", id);

        // TERMINATION
        if (strcmp(id, "exit") == 0 || strcmp(id, "EXIT") == 0)
        {
            printf("\nExiting voting system...\n");
            saveProgress();
            updateVoterStatusFile();
            saveResultsToFile();
            showLeaderboard();
            exit(0);
        }

        printf("Enter Password: ");
        scanf("%s", pass);

        voterIndex = login(id, pass);

        if (voterIndex == -1)
        {
            printf("\nInvalid credentials!\n");
            totalInvalidAttempts++;
            saveProgress();
            continue;
        }

        if (hasVoted[voterIndex] == 1)
        {
            printf("\nYou have already voted!\n");
            writeLog("Duplicate vote attempt");
            totalInvalidAttempts++;
            saveProgress();
            continue;
        }

        castVote(voterIndex);
    }

    printf("All voters have voted!");
    showLeaderboard();

    exit(0);
}
